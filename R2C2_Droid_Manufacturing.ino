#include <HMC5883L.h>

//Pin 7 LED
int Whiteled = 7;
int Grnled = 6;
int Ylwled = 5;
int Rdled = 4;
int sensorValue = 0;
const int analogInPin = A0;

int pwm_a = 3;
int pwm_b =

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
      Serial.print(sensorVoltage);

  //Input Reading
    sensorValue = analogRead(analogInPin);
    Serial.print("sensorValue = ");
    Serial.println(sensorValue);

  //Turn all LEDs off
  //Turn on
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);

  //First
  if(sensorVoltage>0.75){
    digitalWrite(4, HIGH);
  }

  if(sensorVoltage>1.5){
    digitalWrite(5, HIGH);
  }

  if(sensorVoltage>2.25){
    digitalWrite(6, HIGH);
  }

  if(sensorVoltage>3.0){
    digitalWrite(7, HIGH);
  }
  delay(50);

    /* delay(sensorValue);
    digitalWrite(4, HIGH);
    delay(sensorValue);
    digitalWrite(5, HIGH);
    delay(sensorValue);  
    digitalWrite(6, HIGH);
    delay(sensorValue);
    digitalWrite(7, HIGH); */

} 
