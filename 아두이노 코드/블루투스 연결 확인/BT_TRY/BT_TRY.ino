
#include <SoftwareSerial.h>

//#include "DHT.h"

SoftwareSerial BTSerial(10, 11);  // RX, TX
//HC-06의 TX : 아두이노의 디지털 핀 10에 연결
//HC-06의 RX : 아두이노의 디지털 핀 11에 연결
//즉, HC-06의 TX 핀에서 데이터를 아두이노의 RX핀으로 전달하고, HC-06의 RX핀은 아두이노의 TX 핀에서 데이터를
//받게 됩니다. 
//HC-06 TX → 아두이노 10번 핀 (BTSerial의 RX 역할)
//HC-06 RX → 아두이노 11번 핀 (BTSerial의 TX 역할)
/*
int fanPint = 7; // 팬모터가 연결된 핀
int mosfetPin = 6;
int cdsPin = A0; // 조도센서 핀
int tempPin = 8;

int thresholdBright = 110; // 밝기 임계값 (조도 센서 값)
int thresholdDark = 540; // 어두운 환경의 임계값


unsigned long previousMillis = 0;
const long interval = 1000; // 1초 간격

DHT dht(tempPin, DHT22);
*/
void setup() 
{
  /*
  pinMode(fanPin, OUTPUT);
  pinMode(mosfetPin, OUTPUT); // 팬모터 핀을 출력으로 설정
*/
  Serial.begin(9600);
  BTSerial.begin(9600);
  /*
  dht.begin();
  */
}
/*
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

      if(nowtemperature >= temperature)
      {
        analogWrite(mosfetPin, 255);   // PDLC 필름 불투명
        digitalWrite(fanPin, HIGH);    // 팬모터 작동
      }
      else if(nowtemperature < temperature)
      {
        digitalWrite(fanPin, LOW);
        analogWrite(mosfetPin, 0);      // PDLC 필름 투명
      }

    } 
    else if (received == 'W') 
    {  // 창 투명도 조절 명령
      int opacity = BTSerial.parseInt();
      Serial.print("창의 투명도: ");
      Serial.println(opacity);
      Serial.println("창의 투명도를 조절하겠습니다.")

      if(oparcity == 0)
      {
        analogWrite(mosfetPin, 255); // 필름 투명도0 = 완전 불투명
      }
      else if(oparcity == 20)
      {
        analogWrite(mosfetPin, 185); // 필름 투명도20 = 반투명
      }
      else if(oparcity == 40)
      {
        analogWrite(mosfetPin, 105); // 필름 투명도40 = 반투명
      }
      else if(oparcity == 60)
      {
        analogWrite(mosfetPin,  65); // 필름 투명도60 = 반투명
      }
      else if(oparcity == 80)
      {
        analogWrite(mosfetPin, 25); // 필름 투명도80 = 반투명
      }
      else if(oparcity == 100)
      {
        analogWrite(mosfetPin, 0); // 필름 투명도100 = 완전 투명
      }
      
    }
  }


  }



  
}
*/

/*
//블루투스 모듈 정상 작동 확인용 코드
void loop(){
  if (BTSerial.available()) {
    Serial.write(BTSerial.read());
  }
  if (Serial.available()) {
    BTSerial.write(Serial.read());
  }
}
*/

void loop() {
  if (BTSerial.available()) {
    char received = BTSerial.read();
    Serial.print("Received from BT: ");
    Serial.println(received);  // 수신된 데이터 디버깅 출력
  }
  if (Serial.available()) {
    char fromSerial = Serial.read();
    BTSerial.print(fromSerial);  // 시리얼 모니터에서 블루투스로 전송
    Serial.print("Sent to BT: ");
    Serial.println(fromSerial);
  }
}
