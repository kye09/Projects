#include "WiFiEsp.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h> 

#define rxPin 3
#define txPin 2
#define TRIGPIN 12
#define ECHOPIN 13
#define CTM 10
#define ONE_DAY_MILLIS 86400000

SoftwareSerial esp01(txPin, rxPin); // SoftwareSerial NAME(TX, RX);

char ssid[21] = "IoT";    // your network SSID (name)
char pass[21] = "qwer1234";  // your network password 
int status = WL_IDLE_STATUS;        // the Wifi radio's status

float tempSum = 0;
float tempAvg=0;
int weather = 0;
int weatherSum = 0;

int dur;
float dis;

int piezo = 6;
int numTones = 8;
int tones[] = {261, 294, 330, 349, 392, 440, 494, 523};

LiquidCrystal_I2C lcd(0x3F, 16, 2);

const char* host = "apis.data.go.kr";
const char KOR_HEAD[] PROGMEM       = "http://apis.data.go.kr/1360000/VilageFcstInfoService_2.0/";
const char KOR_GVLF[] PROGMEM       = "getVilageFcst";   // 단기예보조회
const char KOR_ADD0[] PROGMEM       = "?serviceKey=";
const char KOR_KEY[] PROGMEM        = "5Owwy2KOuJAjVdUMndm%2FYs9dzGSWjyObxJIJs8VNdfDhw7%2Bc6utcs9X5mSXfgSMG9e4DMQvbdQfbayAkTBhJIA%3D%3D"; //인증키 
const char KOR_ADD1[] PROGMEM       = "&numOfRows=";
const char KOR_ADD2[] PROGMEM       = "&pageNo=";
const char KOR_ADD3[] PROGMEM       = "&dataType=JSON&base_date=";
const char KOR_ADD4[] PROGMEM       = "&base_time=";
const char KOR_ADD5[] PROGMEM       = "&nx=";
const char KOR_ADD6[] PROGMEM       = "&ny=";

WiFiEspClient client; // WiFiEspClient 객체 선언

void setup() {
  Serial.begin(9600);  //시리얼모니터
  esp01.begin(9600);   //와이파이 시리얼
  delay(1000);
  WiFi.init(&esp01);   // initialize ESP module

  pinMode(LED_BUILTIN, OUTPUT); // LCD 패널을 출력으로 설정
  pinMode(piezo, OUTPUT);
  pinMode(TRIGPIN,OUTPUT);
  pinMode(ECHOPIN, INPUT);

  lcd.init(); // LCD 초기화
  lcd.backlight(); // LCD 배경조명
  lcd.clear(); // LCD 화면 지우기
  lcd.print("Temperate");
  lcd.setCursor(0, 1); // 두 번째 줄로 커서 이동
  // lcd.print(""); 
  

  while ( status != WL_CONNECTED) {   // attempt to connect to WiFi network
    Serial.print(F("Attempting to connect to WPA SSID: "));
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);    // Connect to WPA/WPA2 network
  }
  // if (status == WL_CONNECTED) Serial.println(F("You're connected to the network"));
  // Serial.println();
   if (status == WL_CONNECTED) {
    Serial.println(F("You're connected to the network"));
  } else {
    Serial.println(F("Failed to connect to Wi-Fi"));
    // 오류 메시지 또는 디버그 정보를 추가로 출력할 수 있습니다.
  }
  Serial.println();


}

#define PI 3.1415926535897932384626433832795

int nx, ny;
// 위도 경도로 격자 값 계산
void getGride(float lat, float lon ) {
  float ra;
  float theta;
  float RE = 6371.00877;   // 지구 반경(km)
  float GRID = 5.0;        // 격자 간격(km)
  float SLAT1 = 30.0;      // 투영 위도1(degree)
  float SLAT2 = 60.0;      // 투영 위도2(degree)
  float OLON = 126.0;      // 기준점 경도(degree)
  float OLAT = 38.0;       // 기준점 위도(degree)
  float XO = 43;           // 기준점 X좌표(GRID)     
  float YO = 136;          // 기1준점 Y좌표(GRID)
  float DEGRAD = PI / 180.0;
  float RADDEG = 180.0 / PI;
  float re = RE / GRID;
  float slat1 = SLAT1 * DEGRAD;
  float slat2 = SLAT2 * DEGRAD;
  float olon = OLON  * DEGRAD;
  float olat = OLAT  * DEGRAD;
  float sn = tan( PI * 0.25f + slat2 * 0.5f ) / tan( PI * 0.25f + slat1 * 0.5f );
  sn = log(cos(slat1) / cos(slat2)) / log(sn);
  float sf = tan(PI * 0.25f + slat1 * 0.5f);
  sf = pow(sf, sn) * cos(slat1) / sn;
  float ro = tan(PI * 0.25f + olat * 0.5f);
  ro = re * sf / pow(ro, sn);
  ra = tan(PI * 0.25f + (lat) * DEGRAD * 0.5f);
  ra = re * sf / pow(ra, sn);
  theta = lon * DEGRAD - olon;
  if(theta > PI) theta -= 2.0f * PI;
  if(theta < -PI) theta += 2.0f * PI;
  theta *= sn;
  nx = int(floor(ra * sin(theta) + XO + 0.5f));
  ny = int(floor(ro - ra * cos(theta) + YO + 0.5f));
  Serial.print(F("nx: ")); Serial.println(nx);
  Serial.print(F("ny: ")); Serial.println(ny);
}

// 예보 기준 시간: 2, 5, 8, 11, 14, 17, 20, 23 
float lat = 37.64;  // 위도 
float lon = 126.06; // 경도
uint8_t checkTime = 2; 
uint32_t dateTime = 20231214; // 최근 3일간의 자료만 제공
uint8_t Rows = 12; 
uint8_t pageNum = 1;
uint8_t totalPage = 23;
bool getNext = true; 

// 기온, 하늘상태, 습도, 강우 변수
float  Temp[8] = { 0, }; // 00, 03, 06, 09, 12, 15, 18, 21
uint8_t Sky[8]  = { 0, }; // 맑음(1), 구름 많음(3), 흐림(4)
uint8_t Reh[8]  = { 0, }; // 습도 (문자열 표시)
uint8_t Pop[8]  = { 0, }; // 없음(0), 비(1), 비/눈(2), 눈(3), 소나기(4)
//시간 체크
String convertTime(uint8_t checkTime) {
  String temp;
  if (checkTime < 100) { temp += '0'; temp += checkTime; }
  else temp += checkTime;
  temp += F("00");
  return temp;
}

bool finished = true;
uint8_t count = 0;
uint8_t failCount = 0;

// api 날씨 요청을 
void get_weather(uint32_t date, String bsTime, uint8_t Rows, uint8_t pageNum) {
  Serial.println(F("Starting connection to server..."));
  if (client.connect(host, 80)) {
    Serial.println(F("Connected to server"));
    client.print(F("GET "));
    client.print((const __FlashStringHelper *)KOR_HEAD);
    client.print((const __FlashStringHelper *)KOR_GVLF);
    client.print((const __FlashStringHelper *)KOR_ADD0);
    client.print((const __FlashStringHelper *)KOR_KEY);
    client.print((const __FlashStringHelper *)KOR_ADD1);
    client.print(Rows);
    client.print((const __FlashStringHelper *)KOR_ADD2);
    client.print(pageNum);
    client.print((const __FlashStringHelper *)KOR_ADD3);
    client.print(date);
    client.print((const __FlashStringHelper *)KOR_ADD4);
    client.print(bsTime);
    client.print((const __FlashStringHelper *)KOR_ADD5);
    client.print(nx);
    client.print((const __FlashStringHelper *)KOR_ADD6);
    client.print(ny);
    client.print(F(" HTTP/1.1\r\nHost: "));
    client.print(host);
    client.print(F("\r\nConnection: close\r\n\r\n"));
    getNext = false;
  } else {
    failCount++; delay(500); 
    Serial.println(failCount);
    if (failCount > 10) {
      while (client.available()) char c = client.read();
      Serial.println(F("Failed & Finished the task")); 
      failCount = 0; finished = true; count = 0; pageNum = 1; getNext = true; 
    }
  }
}

// 초음파 센서 거리 인식 함수
float measureDistance() { 
  digitalWrite(TRIGPIN, HIGH);
  delayMicroseconds(CTM);
  digitalWrite(TRIGPIN, LOW);
  dur = pulseIn(ECHOPIN, HIGH);
  dis= (float)dur * 0.017;
  delay(500);
  return dis;
}
// 부저 울리는 함수
void activateBuzzer() {
  tone(piezo, tones[0], 1000);
}

bool checkRain = false;

void loop() {


  if (!finished) {
    while (count < totalPage) {
      if (getNext) {
        if (count == 0) getGride(lat, lon); // 위도, 경도
        String cTime = convertTime(checkTime);
        Serial.println(F("--------------------"));
        Serial.print(dateTime); Serial.print('/'); Serial.println(cTime); 
        Serial.print(Rows);Serial.print('/');Serial.println(pageNum);
        get_weather(dateTime, cTime, Rows, pageNum);
      }
      if (client.available()) {
        bool check = false; 
        while (client.available()) { check = client.find("["); if (check) break; }
        Serial.println(F("OK")); 
        if (check) { //날씨 데이터 파싱
          float value = 0; uint8_t timeVal = 255; uint8_t rowC = 0; char cc;
          String line0, cat; 
          while (client.available()) {
            while (rowC < Rows) {
              for (uint8_t i = 0; i < 3; i++) check = client.find(":"); 
              cc = client.read(); cc = 'a'; cat = ""; 
              while (cc != '"') { cc = client.read(); if (cc != '"') cat += cc; }
              for (uint8_t i = 0; i < 2; i++) check = client.find(":"); 
              cc = client.read(); line0 = ""; 
              line0 += char(client.read()); line0 += char(client.read());
              timeVal = line0.toInt(); line0 = "";
              bool save = false;
              if (timeVal == 0 || timeVal == 3 || timeVal == 6 || timeVal == 9 
                          || timeVal == 12 || timeVal == 15 || timeVal == 18 || timeVal == 21) save = true;
              if (save) {
                check = client.find(":"); cc = client.read(); cc = 'a';
                while (cc != '"') { cc = client.read(); if (cc != '"') line0 += cc; }
                value = line0.toFloat(); line0 = "";
              }
              check = client.find("}"); 
              if (save) {
                if (cat == F("TMP")) Temp[timeVal/3] = value;           
                else if (cat == F("SKY")) Sky[timeVal/3] = uint8_t(value); 
                else if (cat == F("REH")) Reh[timeVal/3] = uint8_t(value);
                else if (cat == F("PTY")) { 
                  if (uint8_t(value) == 0) Pop[timeVal/3] = 0;
                  else checkRain = true;
                } else if (checkRain && cat == F("PCP")) {
                  if (uint8_t(value) != 0) { Pop[timeVal/3] = uint8_t(value); checkRain = false; }
                } else if (checkRain && cat == F("SNO")) {
                  if (uint8_t(value) != 0) Pop[timeVal/3] = uint8_t(value); 
                  else Pop[timeVal/3] = 0;  
                  checkRain = false; 
                }
              }
              rowC++; 
            }
            while (client.available()) cc = client.read();
          }
          count++; getNext = true; pageNum++; failCount = 0;
        } else {
          Serial.println(F("No Data, check Date & time")); 
          getNext = true; failCount++;
          Serial.println(failCount);
          if (failCount > 3) {
            while (client.available()) char c = client.read();
            Serial.println(F("Failed & Finished the task")); 
            failCount = 0; finished = true; count = 0; pageNum = 1; getNext = true; 
            break;
          }
        }
        if (count == totalPage) {  // 결과값을 시리얼 모니터에 출력
          finished = true; checkRain = false; 
          for (int i = 0; i < 8; i++) { Serial.print(Temp[i]); Serial.print(','); }
          Serial.println();
          for (int i = 0; i < 8; i++) { Serial.print(Sky[i]); Serial.print(','); }
          Serial.println();
          for (int i = 0; i < 8; i++) { Serial.print(Reh[i]); Serial.print(','); }
          Serial.println();
          for (int i = 0; i < 8; i++) { Serial.print(Pop[i]); Serial.print(','); }
          Serial.println();
        }
        
      }
      if (finished)break;

    }
    count = 0; pageNum = 1; 
  }

  tempSum = 0;

for (int i = 0; i < 8; i++) { //평균기온
          tempSum += Temp[i];
      }
        tempAvg = (float)tempSum / 8;

int max=Temp[0];
int min=Temp[0];

for (int i = 0; i <8; i++) {
      if(Temp[i]>max){
        max=Temp[i];
      }
}
for (int i = 0; i <8; i++) {
      if(Temp[i]<min){
        min=Temp[i];
      }
}
int k = 0;
int y = 0;

for (int i=0; i <8; i ++) {
  if (Sky[i]==1){
    k++;
  }
  else{
    y++;
  }
}
  
      lcd.setCursor(10, 0);
      lcd.print(tempAvg); // 평균기온 출력
      lcd.print((char)223);
      lcd.print("C");
      lcd.setCursor(1, 1);
      lcd.print(min); //최저기온
      lcd.print("/");
      lcd.print(max); //최고기온
      lcd.print((char)223);
      lcd.print("C");
      if (y>k) { // 하늘 상태
       lcd.setCursor(9, 1);
       lcd.print("Cloudy");
       
  }
   else if (k>y) {// 하늘 상태
    lcd.print("    "); 
    lcd.setCursor(10, 1);
    lcd.print("Sunny");
   }
      lcd.print("   "); //lcd 화면 클리어를 위한 공백
      delay(500); // 대기
      

      float distance = measureDistance(); //사람 감지
      Serial.println(distance);
      delay(500);
    if (distance<=50) {
             weather = 0;
        for (int i = 0; i < 8; i++) {  // Pop 배열의 값이 0이 아니면 부저 울리기
           weather +=Pop[i];
        }
          if (weather != 0) {
            activateBuzzer(); 
            delay(500);
          }
        }
        
      

  if(Serial.available() > 0){
    String temp = Serial.readStringUntil('\n');
    Serial.println(temp);
    if (temp == "1") {  // 시리얼 모니터에서 날씨정보 수동요청 (enter : 1)
      finished = !finished;
    }
  }
}
