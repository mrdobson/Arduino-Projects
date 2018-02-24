int motorPin = A0;
int blinkPin = 13;

int watertime = 5000; // how long to water in miliseconds
int waittime = 5000; // how long to wait between watering

void setup()
{
  pinMode(motorPin, OUTPUT);
  pinMode(blinkPin, OUTPUT);
}

void loop()
{
  digitalWrite(motorPin, HIGH);
  digitalWrite(blinkPin, HIGH);
  delay(watertime);
  digitalWrite(motorPin, LOW);
  digitalWrite(blinkPin, LOW);
  delay(waittime);
}
