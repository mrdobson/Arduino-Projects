#include <SoftwareSerial.h>

// SparkFun Soil Moisture Sensor and Serial LCD example 1
// By Sarah Al-Mutlaq 2015
// Sketch reads sensor and desplays level and whether soil is wet or dry

// Use the softwareserial library to create a new "soft" serial port
// for the display. This prevents display corruption when uploading code.

// Here we are setting up some water thersholds that we will 
// use later. Note that you will need to change these to match
// your soil type and environment. 

int thresholdUp = 400;
int thresholdDown = 250;

// We are setting up the pin A0 on the redboard to be our sensor
// pin input:

int sensorPin = A0;


void setup(){
  Serial.begin(9600); // set up serial port for 9600 baud (speed)
}

void loop(){


  // We need to set up a pin to get the value that the soil 
  // moisture sensor is outputting, so sensorValue will get the
  // analog value from the sensor pin A0 on the redboard that we 
  // set up earlier.

  int sensorValue;
  sensorValue = analogRead(sensorPin);

  //Write what we want to desplay on the screen:
  Serial.write("Water Level: ");
  Serial.print(sensorValue); //Using .print instead of .write for values

  // Now we are going to check if the water level is below a 
  // out thresholdDown value we set earlier, and if it is have 
  // words "Dry, Water it!" display one column over on the first 
  // row:

  if (sensorValue <= thresholdDown){
    // move cursor to beginning of second line on LCD:
    DisplayWords = "TOO DRY AHMAHGAD";
    Serial.write(DisplayWords);

  // If the value is not below our thresholdDown value we want to 
  // check if it is above our thresholdUp value, and if it is 
  // change the display words to "Wet, Leave it!":



  } else if (sensorValue >= thresholdUp){
    
    DisplayWords = "TOO WET WHAT";
    Serial.Write(DisplayWords);

  // Otherwise if it is inbetween the two values we want it to 
  // the display it had, so if our soil was really wet and drying 
  // the words would only change to "Dry, Water it!" when it got to the lower threshold
  // (thresholdDown), but if it was dry and getting wetter the words
  // would only change to "Wet, Leave it!" when it got to the upper 
  // threshold (thresholdUp_):

  } 

  delay(500); //wait for half a second, so it is easier to read
}

