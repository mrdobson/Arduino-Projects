// !!!! THIS PROGRAM IS MISSING FLOW CONTROL CODE

#include <Wire.h>
#include <SFE_BMP180.h>

#include <Time.h>
#include <TimeLib.h>

#define TIME_HEADER  "T"   // Header tag for serial time sync message
#define TIME_REQUEST  7    // ASCII bell character requests a time sync message 

  int tmp102Address = 0x48; 
  
  int sensorPin = A0;     // Moisture Sensor Analog Read
  int sensorValue = 0;    // variable to store the value coming from the moisture sensor
  int ActivateSensor = 3; // PWM Pin that controls moisture sensor power
  int YLWLED = 4;         // LED designating water level too low!
  int REDLED = 2;         // LED designating temperature too high!

  // Create an SFE_BMP180 object, here called "pressure":
  SFE_BMP180 pressure;

  #define ALTITUDE 1655.0 // Altitude in meters for Colorado-ish
  





void setup() {
 Serial.begin(9600);
 Wire.begin();

/*
  pinMode(13, OUTPUT);
  setSyncProvider( requestSync);
*/
    
      digitalWrite(ActivateSensor, LOW);      //Start outputs as a low
      digitalWrite(YLWLED, LOW); 
      digitalWrite(REDLED, LOW);
      
        pinMode(ActivateSensor, OUTPUT);      //Initialize Outputs DON'T KEEP FORGETTING TO DO THIS GOD DAMMIT
        pinMode(YLWLED, OUTPUT);
        pinMode(REDLED, OUTPUT);
    
  //initial line
    Serial.println("Temp (*F) \t Temp (*C) \t MoiLev");

    delay(1000);
}



void loop() {

/*
// Clock
  if (Serial.available()) {
    processSyncMessage();
  }
  if (timeStatus()!= timeNotSet) {
    digitalClockDisplay();  
  }  //Uncertain if necessary
  if (timeStatus() == timeSet) {
    digitalWrite(13, HIGH); // LED on if synced
  } else {
    digitalWrite(13, LOW);  // LED off if needs refresh
  }
*/

// Moisture Sensors
  digitalWrite(ActivateSensor, HIGH);
  
  sensorValue = analogRead(sensorPin);

     if (sensorValue > 550) //Moisture Level Okay!
      {
        digitalWrite(YLWLED, LOW);
      }

     if (sensorValue < 550) //Moisture Level too low!
      {
        digitalWrite(YLWLED, HIGH);
      }

  float celsius = getTemperature();
  float fahrenheit = (1.8 * celsius) + 32;

     if (celsius > 27)
      {
        digitalWrite(REDLED, HIGH);
      }


//CSV Export          
        Serial.println("");  
     Serial.print(celsius, DEC);      // send the first value   
        Serial.print("\t");           // separated by a comma
     Serial.print(fahrenheit, DEC);   // other values get sent as above  
        Serial.print("\t"); 
     Serial.print(sensorValue, DEC);
        Serial.println("");
     /*
     Serial.print(hour, DEC);  
        Serial.print("\t");
     Serial.print(minute, DEC);  
        Serial.println();             // print a linefeed character  
     */
     
  digitalWrite(ActivateSensor, LOW);
      
        delay(5000);

}

/*
void processSyncMessage() {
  unsigned long pctime;
  const unsigned long DEFAULT_TIME = 1357041600; // Jan 1 2013

  if(Serial.find(TIME_HEADER)) {
     pctime = Serial.parseInt();
     if( pctime >= DEFAULT_TIME) { // check the integer is a valid time (greater than Jan 1 2013)
       setTime(pctime); // Sync Arduino clock to the time received on the serial port
     }
  }
}
*/

float getTemperature(){
  Wire.requestFrom(tmp102Address,2); 

  byte MSB = Wire.read();
  byte LSB = Wire.read();

  //it's a 12bit int, using twos compliment for negative
  int TemperatureSum = ((MSB << 8) | LSB) >> 4; 

  float celsius = TemperatureSum*0.0625;
  return celsius; 
}

/*
time_t requestSync()
{  
  return 0; // the time will be sent later in response to serial mesg
}
*/
