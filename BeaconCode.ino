#include <SoftwareSerial.h>

/*
CentralBeacon
 Base Station Beacon will transmit its vector to be received by a robot
 Initial V 1.1
 Jan 25 2012
 Brian Sanders
 Robotics Challenge
 
External Interfaces.
Arduino Uno Pin Definitions to interface to the Transceiver.
Digital Pin 7 goes to the Transceiver "TXRXPin"
Digital Pin 6 goes to the Transceiver "PDNPin"
TX out of Arduino is connected to the "DATA" pin

Mode Pins
Digital Pin 5 - Used to select (0) Normal Compass Mode or (1) Analog Voltage as an input source
Analog Pin 0  - Used as in input voltage source to control Beacon transmitting vector.
 
 Updates 
 V1.01  7 Feb 2011 Cleaning up code
 V1.1  25 Jan 2012 Update for Arduino 1.0.  Rename file CentralBeacon.ino
 V1.2  05 Feb 2012 Add functionality for Simulator driven by pot on Analog pin 0
 V1.3  10 Feb 2014 Added comments for clarity
 */

#include <Wire.h> 

//I2C Address for Compass Module HMC6352
int compassAddress = 0x42 >> 1;  // From datasheet compass address is 0x42
// shift the address 1 bit right, the Wire library only needs the 7
// most significant bits for the address

//  temporary variable used for compass
int reading = 0; 
int currentVector = 0;      //value of current heading or vector

// Arduino Uno Pin Definitions to interface to the Transceiver.
const int TXRXPin = 7;
const int PDNPin = 6;
const int ManualVectorMode = 5;  // Logic High equates to using Analog port.
const int AnalogVectorPin = 0;

void setup() {

  // Start of I2C
  Wire.begin();                // join i2c bus (address optional for master) 

  // Initialize serial communications at 9600 bps:
  Serial.begin(9600);          // start serial communication at 9600bps 

  //set the Transceiver to TX and Power On the Unit
  pinMode(PDNPin, OUTPUT);
  pinMode(TXRXPin, OUTPUT);
  pinMode(ManualVectorMode, INPUT);
  digitalWrite(PDNPin, 1);
  digitalWrite(TXRXPin, 1);

}


void loop() {

  if(digitalRead(ManualVectorMode))
  {
    currentVector= analogRead(AnalogVectorPin);
    currentVector = map(currentVector, 0, 1023, 0, 359);
    
    Serial.println(currentVector/2);  //Uncomment this line if you have it hooked up to your computer and want to see the transmitted vector (0-179)
    delay(100);
  }
  else {
    currentVector = getVector();
  }
  Serial.print("FF");  //bit pattern high then alternating high low for 
  Serial.print(1);  //Station ID
  // 360 deg is represented in 3 hex characters
  Serial.write(currentVector/2); //scale the transmitted vector down by 2 to fit in the 0-180 range of 1B 
  Serial.print("U");
}


int getVector ()
{
  //http://wiring.org.co/learning/libraries/hmc6352sparkfun.html
  //On most Arduino boards, SDA (data line) is on analog input pin 4, and SCL (clock line) is on analog input pin 5.

  // step 1: instruct sensor to read echoes 
  Wire.beginTransmission(compassAddress);  // transmit to device
  // the address specified in the datasheet is 66 (0x42) 
  // but i2c adressing uses the high 7 bits so it's 33 
  Wire.write('A');          // command sensor to measure angle  
  Wire.endTransmission();  // stop transmitting 

  // step 2: wait for readings to happen 
  delay(10);               // datasheet suggests at least 6000 microseconds 

  // step 3: request reading from sensor 
  Wire.requestFrom(compassAddress, 2);  // request 2 bytes from slave device #33 

  // step 4: receive reading from sensor 
  if(2 <= Wire.available())     // if two bytes were received 
  { 
    reading = Wire.read();   // receive high byte (overwrites previous reading) 
    reading = reading << 8;     // shift high byte to be high 8 bits 
    reading += Wire.read();  // receive low byte as lower 8 bits 
    reading /= 10;
    return(reading);    // print the reading 
  } 
}




