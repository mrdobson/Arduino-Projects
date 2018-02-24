int sensorPin = A0;    // select the input pin for the potentiometer
int sensorValue = 0;   // variable to store the value coming from the sensor
int ActivateSensor = 3;
int YLWLED = 4;        //Yellow LED on panel 
 
void setup() {
   Serial.begin(9600); 
    digitalWrite(ActivateSensor, LOW);
    digitalWrite(YLWLED, LOW); 
      pinMode(ActivateSensor, OUTPUT);
      pinMode(YLWLED, OUTPUT);
}
 
void loop() {
  // read the value from the sensor:
  digitalWrite(ActivateSensor, HIGH);
  
  sensorValue = analogRead(sensorPin);

    if (sensorValue > 550)
    {
      Serial.println("");
      Serial.println("Water is A-okay desu! :D");
      digitalWrite(YLWLED, LOW);
    }

    if (sensorValue < 550)
    {
      Serial.println("");
      Serial.println("Need more water kupo! D:");
      digitalWrite(YLWLED, HIGH);
    }
            
  Serial.print("Moisture Level = " );                       
  Serial.println(sensorValue);
    delay(1000);
  digitalWrite(ActivateSensor, LOW);
    delay(10000);
}
