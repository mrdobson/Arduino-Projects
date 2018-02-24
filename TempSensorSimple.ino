
//Arduino 1.0+ Only
//Arduino 1.0+ Only

//////////////////////////////////////////////////////////////////
//©2011 bildr
//Released under the MIT License - Please reuse change and share
//Simple code for the TMP102, simply prints temperature via serial
//////////////////////////////////////////////////////////////////

#include <Wire.h>
int tmp102Address = 0x48;

int REDLED1 = 2;

void setup(){
  Serial.begin(9600);
  Wire.begin();
}

void loop(){

  //Turn off all LEDs at the start of loop
  digitalWrite(REDLED1, LOW);

  float celsius = getTemperature();
  Serial.print("Celsius: ");
  Serial.println(celsius);

  if (celsius > 27)
  {
    Serial.println("");
    Serial.println("HOT. TOO HOT.");
    digitalWrite(REDLED1, HIGH);
  }

    Serial.println("");
  
  float fahrenheit = (1.8 * celsius) + 32;  
  Serial.print("Fahrenheit: ");
  Serial.println(fahrenheit);

  delay(2000); //just here to slow down the output. You can remove this
}

float getTemperature(){
  Wire.requestFrom(tmp102Address,2); 

  byte MSB = Wire.read();
  byte LSB = Wire.read();

  //it's a 12bit int, using two's compliment for negative
  int TemperatureSum = ((MSB << 8) | LSB) >> 4; 

  float celsius = TemperatureSum*0.0625;
  return celsius;
}

