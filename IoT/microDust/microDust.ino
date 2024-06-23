#include <SoftwareSerial.h>
#include <WiFiEsp.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define TRIGPIN 12
#define ECHOPIN 13
#define CTM 10

LiquidCrystal_I2C lcd(0x3F, 16, 2);

char ssid[] = "IoT";
char password[] = "qwer1234";
char host[] = "apis.data.go.kr"; // XML을 요청할 호스트 주소

int dur;
float dis;

int pm10Value;

float distance = 0;

int piezo = 6;
int numTones = 8;
int tones[] = {261, 294, 330, 349, 392, 440, 494, 523};

#define RED_LED 11
#define GREEN_LED 10
#define BLUE_LED 9

SoftwareSerial espSerial(2, 3); // ESP01 모듈을 소통하기 위한 소프트웨어 시리얼 객체

bool finished = true;

void setup() {
  Serial.begin(9600);
  espSerial.begin(9600);

  WiFi.init(&espSerial); // WiFiEsp 라이브러리 초기화

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println(WiFi.status());

  lcd.init();
  lcd.backlight();
  lcd.clear(); // LCD 화면 지우기
  lcd.print("Micro Dust");

  pinMode(piezo, OUTPUT);

  pinMode(TRIGPIN, OUTPUT);
  pinMode(ECHOPIN, INPUT);

  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
}

float measureDistance() {
  digitalWrite(TRIGPIN, HIGH);
  delayMicroseconds(CTM);
  digitalWrite(TRIGPIN, LOW);
  dur = pulseIn(ECHOPIN, HIGH);
  dis = (float)dur * 0.017;
  delay(500);
  return dis;
}

void activateBuzzer() {
  tone(piezo, tones[2], 1000); // 톤은 날씨는 0, 미세먼지는 2, 자외선지수는 4로
  }

void loop() {
  if (!finished) {
    if (WiFi.status() == WL_CONNECTED) {
      WiFiEspClient client;
      if (client.connect(host, 80)) {
        client.print(String("GET /B552584/ArpltnInforInqireSvc/getCtprvnRltmMesureDnsty?serviceKey=1RCLarIn%2BsujNPIOeZ6xx7oG0F%2BL6jjSK1pmRPvMinkCRARxIbs5QXjS3Ng58weCBxcTrXYq5Wk%2F4MORIMMinw%3D%3D&returnType=xml&numOfRows=1&pageNo=39&sidoName=%EC%84%9C%EC%9A%B8&ver=1.0 HTTP/1.1\r\n") +
                       "Host: " + host + "\r\n" +
                       "Connection: close\r\n\r\n");

        while (client.connected()) {
          String line = client.readStringUntil('\n');

          // 예제로 미세먼지 수치를 추출하는 코드
          int pm10ValueIndex = line.indexOf("<pm10Value>");
          if (pm10ValueIndex != -1) {
            String pm10ValueStr = line.substring(pm10ValueIndex + 11, line.indexOf("</pm10Value>"));
            pm10Value = pm10ValueStr.toInt();

            // 여기서부터는 미세먼지 수치에 따른 동작을 수행
            lcd.setCursor(0, 1);
            lcd.print("PM10=");
            lcd.print(pm10Value);

            // 미세먼지 수치에 따라 RGB LED 제어
            if (pm10Value >= 0 && pm10Value <= 30) {
              digitalWrite(RED_LED, LOW);
              digitalWrite(GREEN_LED, LOW);
              digitalWrite(BLUE_LED, HIGH);
            } else if (pm10Value >= 31 && pm10Value <= 80) {
              digitalWrite(RED_LED, LOW);
              digitalWrite(GREEN_LED, HIGH);
              digitalWrite(BLUE_LED, LOW);
            } else if (pm10Value >= 81 && pm10Value <= 150) {
              digitalWrite(RED_LED, HIGH);
              digitalWrite(GREEN_LED, HIGH);
              digitalWrite(BLUE_LED, LOW);
            } else if (pm10Value >= 151) {
              digitalWrite(RED_LED, HIGH);
              digitalWrite(GREEN_LED, LOW);
              digitalWrite(BLUE_LED, LOW);
            }
          }
        }

        client.stop();
      }
    }
    finished = true;
  }

  float distance = measureDistance(); // 함수 불러오기
  Serial.println(distance); // 거리 출력 (없어도 됨)
  delay(500);
  if (distance <= 50) { // 사람이 감지되면
    if (pm10Value >= 81) {
      activateBuzzer(); // 부저 울리기
      delay(500);
    }
  }

  if (Serial.available() > 0) {
    String temp = Serial.readStringUntil('\n');
    Serial.println(temp);
    if (temp == "1") { // 시리얼 모니터에서 날씨정보 수동요청 (enter : 1)
      finished = !finished;
    }
  }
}
