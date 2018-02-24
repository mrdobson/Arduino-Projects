// !!!! THIS PROGRAM IS MISSING FLOW CONTROL CODE

#include <Wire.h>
#include <SFE_BMP180.h>
#include <Time.h>
#include <TimeLib.h>

  int tmp102Address = 0x48; 
  
  int sensorPin = A0;     // I don't know why this is here yet, probably future ouptut of flow control gate
  int sensorValue = 0;    // variable to store the value coming from the moisture sensor
  int ActivateSensor = 3; // PWM Pin that controls moisture sensor power
  int YLWLED = 4;         // LED designating water level too low!
  int REDLED = 2;         // LED designating temperature too high!

  // Create an SFE_BMP180 object, here called "pressure":
  SFE_BMP180 pressure;

  #define ALTITUDE 1655.0 // Altitude in meters for Colorado-ish
  

void setup() {
    Serial.begin(9600);
    
      digitalWrite(ActivateSensor, LOW);      //Start outputs as a low
      digitalWrite(YLWLED, LOW); 
      digitalWrite(REDLED, LOW);
      
        pinMode(ActivateSensor, OUTPUT);      //Initialize Outputs DON'T KEEP FORGETTING TO DO THIS GOD DAMMIT
        pinMode(YLWLED, OUTPUT);
        pinMode(REDLED, OUTPUT);
    
  //BMP Pressure Sensor Section
    Serial.println("REBOOT");
    

    // Initialize the sensor (it is important to get calibration values stored on the device).

    if (pressure.begin())
      Serial.println("BMP180 init success");
    else
    {
      // Oops, something went wrong, this is usually a connection problem,
      // see the comments at the top of this sketch for the proper connections.

      Serial.println("BMP180 init fail\n\n");
      while(1); // Pause forever.
    }
    
    //Simple Temp Sensor Section
      Wire.begin();
}

void loop() {

  // Moisture Sensor Section
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
      
        Serial.print("");
        Serial.print("Moisture Level = " );                       
        Serial.println(sensorValue);
        Serial.print("");
        Serial.print("");
        Serial.print("");
        
        digitalWrite(ActivateSensor, LOW);
          



    

  //BMP Pressure Sensor

    char status;
    double T,P,p0,a;

      // Loop here getting pressure readings every 10 seconds.

      // If you want sea-level-compensated pressure, as used in weather reports,
      // you will need to know the altitude at which your measurements are taken.
      // We're using a constant called ALTITUDE in this sketch:
  
    Serial.println();
    Serial.print("provided altitude: ");
    Serial.print(ALTITUDE,0);
    Serial.print(" meters, ");
    Serial.print(ALTITUDE*3.28084,0);
    Serial.println(" feet");
  
      // If you want to measure altitude, and not pressure, you will instead need
      // to provide a known baseline pressure. This is shown at the end of the sketch.

      // You must first get a temperature measurement to perform a pressure reading.
  
      // Start a temperature measurement:
      // If request is successful, the number of ms to wait is returned.
      // If request is unsuccessful, 0 is returned.

    status = pressure.startTemperature();
    if (status != 0)
    {
      // Wait for the measurement to complete:
      delay(status);

      // Retrieve the completed temperature measurement:
      // Note that the measurement is stored in the variable T.
      // Function returns 1 if successful, 0 if failure.

      status = pressure.getTemperature(T);
      if (status != 0)
      {
        // Print out the measurement:
        Serial.print("temperature: ");
        Serial.print(T,2);
        Serial.print(" deg C, ");
        Serial.print((9.0/5.0)*T+32.0,2);
        Serial.println(" deg F");
      
        // Start a pressure measurement:
        // The parameter is the oversampling setting, from 0 to 3 (highest res, longest wait).
        // If request is successful, the number of ms to wait is returned.
        // If request is unsuccessful, 0 is returned.

        status = pressure.startPressure(3);
        if (status != 0)
        {
          // Wait for the measurement to complete:
          delay(status);

          // Retrieve the completed pressure measurement:
          // Note that the measurement is stored in the variable P.
          // Note also that the function requires the previous temperature measurement (T).
          // (If temperature is stable, you can do one temperature measurement for a number of pressure measurements.)
          // Function returns 1 if successful, 0 if failure.

          status = pressure.getPressure(P,T);
          if (status != 0)
          {
            // Print out the measurement:
            Serial.print("absolute pressure: ");
            Serial.print(P,2);
            Serial.print(" mb, ");
            Serial.print(P*0.0295333727,2);
            Serial.println(" inHg");

            // The pressure sensor returns abolute pressure, which varies with altitude.
            // To remove the effects of altitude, use the sealevel function and your current altitude.
            // This number is commonly used in weather reports.
            // Parameters: P = absolute pressure in mb, ALTITUDE = current altitude in m.
            // Result: p0 = sea-level compensated pressure in mb

            p0 = pressure.sealevel(P,ALTITUDE); // we're at 1655 meters (Boulder, CO)
            Serial.print("relative (sea-level) pressure: ");
            Serial.print(p0,2);
            Serial.print(" mb, ");
            Serial.print(p0*0.0295333727,2);
            Serial.println(" inHg");

            // On the other hand, if you want to determine your altitude from the pressure reading,
            // use the altitude function along with a baseline pressure (sea-level or other).
            // Parameters: P = absolute pressure in mb, p0 = baseline pressure in mb.
            // Result: a = altitude in m.

            a = pressure.altitude(P,p0);
            Serial.print("computed altitude: ");
            Serial.print(a,0);
            Serial.print(" meters, ");
            Serial.print(a*3.28084,0);
            Serial.println(" feet");
          }
          else Serial.println("error retrieving pressure measurement\n");
        }
        else Serial.println("error starting pressure measurement\n");
      }
      else Serial.println("error retrieving temperature measurement\n");
    }
    else Serial.println("error starting temperature measurement\n");



   

  //Simple Temp Sensor Section
  
    float celsius = getTemperature();
      Serial.println("");
      Serial.print("Celsius: ");
      Serial.println(celsius);

    if (celsius > 27)
    {
      Serial.println("");
      Serial.println("HOT. TOO HOT. CHILL THE F OUT.");
      digitalWrite(REDLED, HIGH);
    }
  
    float fahrenheit = (1.8 * celsius) + 32;  
      Serial.print("Fahrenheit: ");
      Serial.println(fahrenheit);
      Serial.print("");
      Serial.print("");
      Serial.print("----- ----- ----- ----- -----");

      //CSV Export
          Serial.println("");  
        
        Serial.print("Temp C");
        Serial.print(",");  
        Serial.print("Temp F");
        Serial.print(",");  
        Serial.print("Moisture Level");  
          
          Serial.println("");  
        
        Serial.print(celsius, DEC);  // send the first value   
        Serial.print(",");                    // separated by a comma
        Serial.print(fahrenheit, DEC);   // other values get sent as above  
        Serial.print(","); 
        Serial.print(sensorValue, DEC);     
        Serial.println();                    // print a linefeed character  
      
          delay(5000);


}

float getTemperature(){
  Wire.requestFrom(tmp102Address,2); 

  byte MSB = Wire.read();
  byte LSB = Wire.read();

  //it's a 12bit int, using twos compliment for negative
  int TemperatureSum = ((MSB << 8) | LSB) >> 4; 

  float celsius = TemperatureSum*0.0625;
  return celsius; 



}
