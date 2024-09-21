/*
#include <SoftwareSerial.h>
#include "DHT.h"

SoftwareSerial BTSerial(10, 11);  // RX, TX

int fanPin = 7; // 팬모터가 연결된 핀
int mosfetPin = 6;
int cdsPin = A0; // 조도센서 핀
int tempPin = 8;

int thresholdBright = 110; // 밝기 임계값 (조도 센서 값)
int thresholdDark = 540; // 어두운 환경의 임계값

unsigned long previousMillis = 0;
const long interval = 1000; // 1초 간격

DHT dht(tempPin, DHT22);

void setup() 
{
  pinMode(fanPin, OUTPUT);
  pinMode(mosfetPin, OUTPUT); // 팬모터 핀을 출력으로 설정

  Serial.begin(9600);
  BTSerial.begin(9600);
  
  dht.begin();
}

void loop() 
{
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;

    int lightLevel = analogRead(cdsPin); // 조도 센서 값 읽기
    Serial.print("Light Level : ");
    Serial.println(lightLevel); // 센서 값 출력

    float nowtemperature = dht.readTemperature();
    Serial.print("Temperature : ");
    Serial.println(nowtemperature);

    if (BTSerial.available()) 
    {
      char received = BTSerial.read();
      if (received == 'T') 
      {  // 온도 조절 명령
        int temperature = BTSerial.parseInt();
        Serial.print("목표 온도: ");
        Serial.println(temperature);
        Serial.println("에어컨을 가동하겠습니다.");

        if (nowtemperature >= temperature)
        {
          analogWrite(mosfetPin, 255);   // PDLC 필름 불투명
          digitalWrite(fanPin, HIGH);    // 팬모터 작동
        }
        else if (nowtemperature < temperature)
        {
          digitalWrite(fanPin, LOW);
          analogWrite(mosfetPin, 0);     // PDLC 필름 투명
        }

      } 
      else if (received == 'W') 
      {  // 창 투명도 조절 명령
        int opacity = BTSerial.parseInt(); // 'oparcity' 오타 수정
        Serial.print("창의 투명도: ");
        Serial.println(opacity);
        Serial.println("창의 투명도를 조절하겠습니다.");

        if (opacity == 0)
        {
          analogWrite(mosfetPin, 255); // 필름 투명도 0 = 완전 불투명
        }
        else if (opacity == 20)
        {
          analogWrite(mosfetPin, 185); // 필름 투명도 20 = 반투명
        }
        else if (opacity == 40)
        {
          analogWrite(mosfetPin, 105); // 필름 투명도 40 = 반투명
        }
        else if (opacity == 60)
        {
          analogWrite(mosfetPin, 65);  // 필름 투명도 60 = 반투명
        }
        else if (opacity == 80)
        {
          analogWrite(mosfetPin, 25);  // 필름 투명도 80 = 반투명
        }
        else if (opacity == 100)
        {
          analogWrite(mosfetPin, 0);   // 필름 투명도 100 = 완전 투명
        }
      }
    }
  }
}
*/


#include <SoftwareSerial.h>
#include "DHT.h"

SoftwareSerial BTSerial(10, 11);  // RX, TX

int fanPin = 7; // 팬모터가 연결된 핀
int mosfetPin = 6;
int cdsPin = A0; // 조도센서 핀
int tempPin = 8;

int thresholdBright = 110; // 밝기 임계값 (조도 센서 값)
int thresholdDark = 330; // 어두운 환경의 임계값

unsigned long previousMillis = 0;
const long interval = 1000; // 1초 간격 10초

int lightLevel = 0;
bool autoBrightnessMode = false;

DHT dht(tempPin, DHT22);

void setup() 
{
  pinMode(fanPin, OUTPUT);
  pinMode(mosfetPin, OUTPUT); // 팬모터 핀을 출력으로 설정

  Serial.begin(9600);
  BTSerial.begin(9600);
  
  dht.begin();
}

void loop() 
{
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;

    lightLevel = analogRead(cdsPin); // 조도 센서 값 읽기
    Serial.print("Light Level : ");
    Serial.println(lightLevel); // 센서 값 출력

    float nowtemperature = dht.readTemperature();
    Serial.print("Temperature : ");
    Serial.println(nowtemperature);
  }

  // 블루투스 데이터가 수신 가능한지 확인
  if (BTSerial.available()) 
  {
    // 명령어와 숫자를 분리하여 처리
    char command = BTSerial.read();  // 명령어 문자 읽기
    delay(10);  // 데이터를 모두 수신할 시간을 주기 위한 지연

    if (BTSerial.available())
    {
      int value = BTSerial.parseInt();  // 명령어 뒤의 숫자 읽기

      if (command == 'T') 
      {  // 온도 조절 명령
        Serial.print("목표 온도: ");
        Serial.println(value);
        Serial.println("에어컨을 가동하겠습니다.");

        float nowtemperature = dht.readTemperature();
        if (nowtemperature >= value)
        {
          analogWrite(mosfetPin, 255);   // PDLC 필름 불투명
          digitalWrite(fanPin, HIGH);    // 팬모터 작동
        }
        else
        {
          digitalWrite(fanPin, LOW);
          analogWrite(mosfetPin, 0);     // PDLC 필름 투명
        }
      }
      else if (command == 'W') 
      {  // 창 투명도 조절 명령
        Serial.print("창의 투명도: ");
        Serial.println(value);
        Serial.println("창의 투명도를 조절하겠습니다.");

        // 투명도에 따라 적절한 PWM 값을 설정
        switch (value)
        {
          case 0:
            analogWrite(mosfetPin, 255); // 완전 불투명
            break;
          case 20:
            analogWrite(mosfetPin, 185); // 반투명 20
            break;
          case 40:
            analogWrite(mosfetPin, 105); // 반투명 40
            break;
          case 60:
            analogWrite(mosfetPin, 65);  // 반투명 60
            break;
          case 80:
            analogWrite(mosfetPin, 25);  // 반투명 80
            break;
          case 100:
            analogWrite(mosfetPin, 0);   // 완전 투명
            break;
          default:
            Serial.println("잘못된 투명도 값입니다."); // 예상치 못한 값 처리
            break;
        }
      }
      else if(command == 'S')
      {
        Serial.println("자동 밝기 모드를 시작합니다.");
        autoBrightnessMode = true;

        //int nowlightLevel = analogRead(cdsPin);

/*
        if (nowlightLevel < thresholdBright)
        {
          // 밝을 때 (조도센서의 숫자가 작을수록 밝은것)
          analogWrite(mosfetPin, 255);   // PDLC 필름 불투명
        }
        else if (thresholdBright <= nowlightLevel && nowlightLevel < thresholdDark)
        {
          analogWrite(mosfetPin, 80);     // PDLC 필름 반투명
        }
        else if(nowlightLevel > thresholdDark)
        {
          analogWrite(mosfetPin, 0);      // PDLC 필름 투명
        }
        */
        /*
        if (nowlightLevel < thresholdBright)
        {
          Serial.println("조도가 밝음: PDLC 불투명");
          analogWrite(mosfetPin, 255);   // PDLC 필름 불투명
        }
        else if (thresholdBright <= nowlightLevel && nowlightLevel < thresholdDark)
        {
          Serial.println("조도가 중간: PDLC 반투명");
          analogWrite(mosfetPin, 80);     // PDLC 필름 반투명
        }
        else if(nowlightLevel > thresholdDark)
        {
          Serial.println("조도가 어두움: PDLC 투명");
          analogWrite(mosfetPin, 0);      // PDLC 필름 투명
        }
        */

      }
      else if(command == 'E')
      {
        Serial.println("자동 밝기 모드를 종료합니다.");
        autoBrightnessMode = false;
        analogWrite(mosfetPin, 255); //PDLC 필름 투명
      }
    }
  }



  if(autoBrightnessMode)
  {
    int nowlightLevel = analogRead(cdsPin);

    if (nowlightLevel < thresholdBright)
    {
      //Serial.println("조도가 밝음: PDLC 불투명");
      analogWrite(mosfetPin, 255);   // PDLC 필름 불투명
    }
    else if (thresholdBright <= nowlightLevel && nowlightLevel < thresholdDark)
    {
      //Serial.println("조도가 중간: PDLC 반투명");
      analogWrite(mosfetPin, 80);     // PDLC 필름 반투명
    }
    else if(nowlightLevel > thresholdDark)
    {
      //Serial.println("조도가 어두움: PDLC 투명");
      analogWrite(mosfetPin, 0);      // PDLC 필름 투명
    }

  }
}

/*
void setup() 
{
  
  Serial.begin(9600);
  
}

int freeRam() {
  extern int __heap_start, *__brkval;
  int v;
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}

void loop() {
  Serial.print("Free RAM: ");
  Serial.println(freeRam());
}
*/
