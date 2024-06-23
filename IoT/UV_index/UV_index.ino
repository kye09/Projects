#include <SoftwareSerial.h>
#include <WiFiEsp.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define TRIGPIN 12
#define ECHOPIN 13
#define CTM 10

LiquidCrystal_I2C lcd(0x3F, 16, 2);

char ssid[] = "olleh_WiFi_D41D";
char password[] = "0000001149";
char host[] = "apis.data.go.kr"; // XML을 요청할 호스트 주소

int dur;
float dis;

int h0;

float distance = 0;

int piezo = 6; // 부저 핀
int numTones = 8;
int tones[] = {261, 294, 330, 349, 392, 440, 494, 523};

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
  
  pinMode(piezo, OUTPUT);
  pinMode(TRIGPIN, OUTPUT);
  pinMode(ECHOPIN, INPUT);

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

// 부저 울리는 함수
void activateBuzzer() {
  tone(piezo, tones[2], 1000); // 톤은 날씨는 0, 미세먼지는 2, 자외선지수는 4로
  }

void loop() {
  if (!finished) {
    if (WiFi.status() == WL_CONNECTED) {
      WiFiEspClient client;
      if (client.connect(host, 80)) {
        client.print(String("GET /1360000/LivingWthrIdxServiceV4/getUVIdxV4?serviceKey=1RCLarIn%2BsujNPIOeZ6xx7oG0F%2BL6jjSK1pmRPvMinkCRARxIbs5QXjS3Ng58weCBxcTrXYq5Wk%2F4MORIMMinw%3D%3D&pageNo=1&numOfRows=10&dataType=XML&areaNo=1135062100&time=2023121314 HTTP/1.1\r\n") +
                    "Host: " + host + "\r\n" +
                    "Connection: close\r\n\r\n");
        
        while (client.connected()) {
          String line = client.readStringUntil('\n');
          
          // 예제로 자외선 수치를 추출하는 코드
          int h0Index = line.indexOf("<h0>");
          if (h0Index != -1) {
            String h0Str = line.substring(h0Index + 26, line.indexOf("</h0>"));
            int h0 = h0Str.toInt();
            
            // 여기서부터는 자외선 수치에 따른 동작을 수행
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("UV index");
            lcd.setCursor(0, 1);
            lcd.print("h0=");
            lcd.print(h0);
            
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
      if (h0 >= 8) {
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