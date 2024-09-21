/*
int mosfetPin = 6;     // PDLC 필름 제어 핀 (IRF520)
int fanPin = 7;        // 팬모터 제어 핀
int cdsPin = A0;       // 조도 센서 핀
int thresholdBright = 500; // 밝기 임계값 (조도 센서 값)
int thresholdDark = 200;   // 어두운 환경의 임계값
int delayTime = 5000;  // 상태 유지 시간 (5초)

void setup() {
  pinMode(mosfetPin, OUTPUT);
  pinMode(fanPin, OUTPUT);
  Serial.begin(9600);  // 조도 센서 값 확인을 위한 시리얼 모니터
}

void loop() {
  int lightLevel = analogRead(cdsPin);  // 조도 센서로부터 값 읽기
  Serial.println(lightLevel);  // 시리얼 모니터로 조도 값 출력

  if (lightLevel > thresholdBright) {
    // 밝을 때
    //digitalWrite(fanPin, HIGH);    // 팬모터 작동
    analogWrite(mosfetPin, 255);   // PDLC 필름 완전 불투명
    delay(delayTime);              // 일정 시간 유지

    //digitalWrite(fanPin, LOW);     // 팬모터 중지
    analogWrite(mosfetPin, 150);   // PDLC 필름 반투명
    delay(delayTime);              // 일정 시간 유지

    analogWrite(mosfetPin, 0);     // PDLC 필름 완전 투명
    delay(delayTime);              // 일정 시간 유지

  } else if (lightLevel < thresholdDark) {
    // 어두울 때
    analogWrite(mosfetPin, 0);     // PDLC 필름 완전 투명
    //digitalWrite(fanPin, LOW);     // 팬모터 중지
  }

  delay(500);  // 짧은 지연 시간으로 주기적으로 센서값 확인
}
*/

int mosfetPin = 6;     // PDLC 필름 제어 핀 (IRF520)
int cdsPin = A0;       // 조도 센서 핀
int thresholdBright = 110; // 밝기 임계값 (조도 센서 값)
int thresholdDark = 540;   // 어두운 환경의 임계값


int fanPin = 7;        // 팬모터 제어 핀

void setup() {
  pinMode(mosfetPin, OUTPUT);
  Serial.begin(9600);  // 조도 센서 값 확인을 위한 시리얼 모니터
}

void loop() {
  int lightLevel = analogRead(cdsPin);  // 조도 센서로부터 값 읽기
  Serial.print("Light Level: ");  // 시리얼 모니터에 "Light Level: " 출력
  Serial.println(lightLevel);  // 시리얼 모니터에 조도 값 출력

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

  //delay(500);  // 짧은 지연 시간으로 주기적으로 센서값 확인
}
