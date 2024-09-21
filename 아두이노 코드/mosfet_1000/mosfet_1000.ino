int mosfetPin = 6;

void setup() {
  pinMode(mosfetPin, OUTPUT);
}

/*
void loop() {
  // 0% 듀티 사이클로 완전투명 상태 유지
  analogWrite(mosfetPin, 0);

  delay(3000);
// 100% 듀티 사이클로 완전불투명 상태 유지
  analogWrite(mosfetPin, 250);
  
  delay(3000);
// 30% 듀티 사이클로 반투명 상태 유지
  analogWrite(mosfetPin, 90);

  delay(3000);
}
*/

void loop() {
  // 0% 듀티 사이클로 완전투명 상태 유지
  analogWrite(mosfetPin, 0);

  delay(3000);

// 30% 듀티 사이클로 반투명 상태 유지
  analogWrite(mosfetPin, 30);

  delay(3000);

  analogWrite(mosfetPin, 60);
  
  delay(3000);

  analogWrite(mosfetPin, 90);
  
  delay(3000);

  analogWrite(mosfetPin, 120);
  
  delay(3000);

  analogWrite(mosfetPin, 140);
  
  delay(3000);

  analogWrite(mosfetPin, 250);
  
  delay(3000);

}