
void setup() {

Serial.begin(9600);
pinMode(4, OUTPUT);
}

void loop() {
  
  digitalWrite(4, HIGH);

  delay(2000);

  digitalWrite(4, LOW);

  delay(2000);


}
