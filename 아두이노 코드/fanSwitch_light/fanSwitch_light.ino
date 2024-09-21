/*
int fanPin = 7; // 팬모터가 연결된 핀
int mosfetPin = 6;
int cdsPin = A0; // 조도센서 핀

int thresholdBright = 110; // 밝기 임계값 (조도 센서 값)
int thresholdDark = 540;   // 어두운 환경의 임계값

//int lightValue = 0; // 조도 센서 값

void setup() {
  pinMode(fanPin, OUTPUT);
  pinMode(mosfetPin, OUTPUT); // 팬모터 핀을 출력으로 설정
  Serial.begin(9600); // 시리얼 모니터 시작
}

void loop() {
  int lightLevel = analogRead(cdsPin); // 조도 센서 값 읽기
  Serial.print("Light Level : ");
  Serial.println(lightLevel); // 센서 값 출력

  if (lightLevel < thresholdBright) 
  {
    // 밝을 때 (조도센서의 숫자가 작을수록 밝은것)
    analogWrite(mosfetPin, 255);   // PDLC 필름 불투명
    digitalWrite(fanPin, HIGH);    // 팬모터 작동

  } 
  else if (thresholdBright<= lightLevel && lightLevel < thresholdDark) 
  {
    digitalWrite(fanPin, LOW);
    analogWrite(mosfetPin, 90);     // PDLC 필름 투명
  }
  else if(lightLevel>thresholdDark)
  {
    digitalWrite(fanPin, LOW);
    analogWrite(mosfetPin, 0);
  }
  delay(10000); // 1초 대기
}
*/

#include "DHT.h"

int fanPin = 7; // 팬모터가 연결된 핀
int mosfetPin = 6;
int cdsPin = A0; // 조도센서 핀

int tempPin = 8;

int thresholdBright = 110; // 밝기 임계값 (조도 센서 값)
int thresholdDark = 540;   // 어두운 환경의 임계값


float tempThresholdHigh = 26.0; //예시 온도 임계값(높은 온도)
float tempThresholdLow = 22.0; //예시 온도 임계값(낮은 온도)


unsigned long previousMillis = 0;
const long interval = 1000; // 1초 간격

DHT dht(tempPin, DHT22);

void setup() 
{
  pinMode(fanPin, OUTPUT);
  pinMode(mosfetPin, OUTPUT); // 팬모터 핀을 출력으로 설정
  //pinMode(tempPin, INPUT);

  Serial.begin(9600); // 시리얼 모니터 시작
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

    float temperature = dht.readTemperature();
    Serial.print("Temperature : ");
    Serial.println(temperature);


    if (lightLevel < thresholdBright) 
    {
      // 밝을 때 (조도센서의 숫자가 작을수록 밝은것)
      analogWrite(mosfetPin, 255);   // PDLC 필름 불투명
      digitalWrite(fanPin, HIGH);    // 팬모터 작동
    } 

    else if (thresholdBright <= lightLevel && lightLevel < thresholdDark) 
    {
      digitalWrite(fanPin, LOW);
      analogWrite(mosfetPin, 80);     // PDLC 필름 반투명
    }

    else if(lightLevel > thresholdDark)
    {
      digitalWrite(fanPin, LOW);
      analogWrite(mosfetPin, 0);      // PDLC 필름 투명
    }
  }

}

//millis() 함수 : millis() 함수는 아두이노가 켜진 이후의 경과 시간을 밀리초 단윌 반환한다.
//이 값을 이용해 비동기적으로 시간을 체크할 수 있다.
//previousMillis와 currentMillis 변수 : 이 변수들은 시간이 얼마나 경과했는지를 확인하는데 사용된다.
//비동기 시간 체크 : delay()를 사용하지 않고 millis()를 통해 1초 간격으로 조도 센서 값을 읽고 팬모터와 PDLC
//필름을 제어한다.
//이 방법으로 릴레이 모듈이 1초 간격으로 꺼졌다 켜졌다 하지 않고, 조도 센서의 값에 따라 팬모터와 PDLC 필름을
//안정적으로 제어할 수 있다.


/*
int fanPin = 7;         // 팬모터가 연결된 핀
int mosfetPin = 6;      // PDLC 필름 제어 핀
int tempPin = 8;        // NTC 써미스터 온도 모듈의 DO 핀이 연결된 디지털 핀

int thresholdTempHigh = 0; // a 온도 이상 임계값
int thresholdTempMid = 1;  // b 온도 이상 임계값

unsigned long previousMillis = 0;
const long interval = 1000; // 1초 간격

void setup() 
{
  pinMode(fanPin, OUTPUT);
  pinMode(mosfetPin, OUTPUT); 
  pinMode(tempPin, INPUT);    // 온도 센서 핀을 입력으로 설정
  Serial.begin(9600);         // 시리얼 모니터 시작
}

void loop() 
{
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) 
  {
    previousMillis = currentMillis;

    int tempValue = digitalRead(tempPin); // 온도 센서 값 읽기 (DO 핀의 디지털 값 읽기)
    Serial.print("Temperature Sensor Value: ");
    Serial.println(tempValue); // 센서 값 출력

    if (tempValue == thresholdTempHigh) 
    {
      // a 온도 이상일 때
      analogWrite(mosfetPin, 255);   // PDLC 필름 불투명
      digitalWrite(fanPin, HIGH);    // 팬모터 작동
    } 
    else if (tempValue == thresholdTempMid) 
    {
      // b 온도 이상 a 온도 미만일 때
      analogWrite(mosfetPin, 0);    // PDLC 필름 반투명
      digitalWrite(fanPin, LOW);     // 팬모터 꺼짐
    }

  }
}
*/
