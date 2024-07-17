const int fanPin = 9;

void setup() 
{
  pinMode(fanPin, OUTPUT);
}

void loop() 
{
  digitalWrite(fanPin, HIGH);
  delay(2000);
  digitalWrite(fanPin, LOW);
  delay(2000);
}
