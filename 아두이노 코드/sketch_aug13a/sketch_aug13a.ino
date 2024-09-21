void setup() {
  pinMode(6, OUTPUT); // 핀 6을 OUTPUT 모드로 설정
}

void loop() {
  digitalWrite(6, HIGH); // 핀 6에 HIGH 신호를 출력 (LED 켜기)
  delay(2000000);           // 1초 동안 대기
  digitalWrite(6, LOW);  // 핀 6에 LOW 신호를 출력 (LED 끄기)
  delay(5000);           // 1초 동안 대기
} // loop() 함수 닫기
