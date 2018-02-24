
//////////////////////////////////////////////////////////////////
//©2011 bildr
//Released under the MIT License - Please reuse change and share
//Simple code for 2 TMP102s, simple read of both sensors in Celsius and Fahrenheit
//////////////////////////////////////////////////////////////////

#include <Wire.h>
int tmp102Address1 = 0x48;
int tmp102Address2 = 0x49;


void setup(){
  Serial.begin(9600);
  Wire.begin();
}

void loop(){


  float celsius1 = readTMP102(tmp102Address1);
  float fahrenheit1 = (celsius1 * 1.8) + 32;  
   
   
  float celsius2 = readTMP102(tmp102Address2);
  float fahrenheit2 = (celsius2 * 1.8) + 32;  

  delay(1000);
}

float readTMP102(int address){
  Wire.requestFrom(address,2); 

  byte MSB = Wire.receive();
  byte LSB = Wire.receive();

  int TemperatureSum = ((MSB << 8) | LSB) >> 4; //it's a 12bit int, using two's compliment for negative

  float celsius = TemperatureSum*0.0625;
  
  return celsius;
}
