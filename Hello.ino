//Pin 7 LED
int Whiteled = 7;
int Grnled = 6;
int Ylwled = 5;
int Rdled = 4;
int sensorValue = 0;
const int analogInPin = A0;

float sensorVoltage = 0.0;

void setup() {
  // by RRCC Droid Manufacturing

  Serial.begin(9600);

    pinMode(Whiteled, OUTPUT);
    pinMode(Grnled, OUTPUT);
    pinMode(Ylwled, OUTPUT);
    pinMode(Rdled, OUTPUT);

    pinMode(analogInPin, INPUT);

}

void loop() {

 /* Serial.println("Help, I'm stuck in an infinite loop!"); */

//beginnings of skynet

    //Convert to volts
      sensorVoltage= sensorValue * (5.0 / 1023.0);
      Serial.print("\t sensorVoltage = ");
      Serial.println(sensorVoltage);

  //Input Reading
    sensorValue = analogRead(analogInPin);
    Serial.print("sensorValue = ");
    Serial.println(sensorValue);

    delay(sensorValue);
    digitalWrite(4, HIGH);
    delay(sensorValue);
    digitalWrite(5, HIGH);
    delay(sensorValue);  
    digitalWrite(6, HIGH);
    delay(sensorValue);
    digitalWrite(7, HIGH);
    
  //Green LED
    digitalWrite(Grnled, HIGH);
    delay(200);
    digitalWrite(Grnled, LOW);
    delay(100);

  //Yellow LED
    digitalWrite(Ylwled, HIGH);
    delay(400);
    digitalWrite(Ylwled, LOW);
    delay(200);

  //Red LED
    digitalWrite(Rdled, HIGH);
    delay(800);
    digitalWrite(Rdled, LOW);
    delay(400);

  //White LED
    digitalWrite(Rdled, HIGH);
    delay(1600);
    digitalWrite(Rdled, LOW);
    delay(800);

  //White SOS
   /* digitalWrite(Whiteled, HIGH);
        Serial.print(".");
    delay(100);
    digitalWrite(Whiteled, LOW);
    delay(100);
    digitalWrite(Whiteled, HIGH);
        Serial.print(".");
    delay(100);
    digitalWrite(Whiteled, LOW);
    delay(100);
    digitalWrite(Whiteled, HIGH);
        Serial.print(".");
    delay(100);
    digitalWrite(Whiteled, LOW);
    delay(500);

    digitalWrite(Whiteled, HIGH);
      Serial.print("-");
    delay(300);
    digitalWrite(Whiteled, LOW);
    delay(300);
    digitalWrite(Whiteled, HIGH);
      Serial.print("-");
    delay(300);
    digitalWrite(Whiteled, LOW);
    delay(300);
    digitalWrite(Whiteled, HIGH);
      Serial.print("-");
    delay(300);
    digitalWrite(Whiteled, LOW);
    delay(500);

    digitalWrite(Whiteled, HIGH);
      Serial.print(".");
    delay(100);
    digitalWrite(Whiteled, LOW);
    delay(100);
    digitalWrite(Whiteled, HIGH);
      Serial.print(".");
    delay(100);
    digitalWrite(Whiteled, LOW);
    delay(100);
    digitalWrite(Whiteled, HIGH);
      Serial.println(".");
    delay(100);
    digitalWrite(Whiteled, LOW);
    delay(750);    */

}
