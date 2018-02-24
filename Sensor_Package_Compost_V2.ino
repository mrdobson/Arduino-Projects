
int sensorPin1 = A0;    // select the input pin for the potentiometer
int sensorPin2 = A1;
int sensorPin3 = A2;
int sensorValue1 = 0;   // variable to store the value coming from the sensor
int sensorValue2 = 0;
int sensorValue3 = 0;
int ActivateSensor1 = 3;
int ActivateSensor2 = 4;
int ActivateSensor3 = 5;
int YLWLED = 10;        //Yellow LED on panel 

#include <SFE_BMP180.h>
#include <Wire.h>
int tmp102Address = 0x48;
int REDLED = 11;

  SFE_BMP180 pressure;

  #define ALTITUDE 1655.0 // Altitude in meters for Colorado-ish


void setup()
{
  Serial.begin(9600);
  Wire.begin();
  

  Serial.println("HI THOM :D");

  
  digitalWrite(ActivateSensor1, LOW);
   digitalWrite(ActivateSensor2, LOW);
    digitalWrite(ActivateSensor3, LOW);
  
  pinMode(ActivateSensor1, OUTPUT);
   pinMode(ActivateSensor2, OUTPUT);
    pinMode(ActivateSensor3, OUTPUT);
    
  pinMode(YLWLED, OUTPUT);
  pinMode(REDLED, OUTPUT);
    digitalWrite(YLWLED, LOW);
    digitalWrite(REDLED, LOW);
  
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

  
}

void loop()
{

  // read the value from the sensor:
  digitalWrite(ActivateSensor1, HIGH);
  digitalWrite(ActivateSensor2, HIGH);
  digitalWrite(ActivateSensor3, HIGH);
  
  sensorValue1 = analogRead(sensorPin1);
  sensorValue2 = analogRead(sensorPin2);
  sensorValue3 = analogRead(sensorPin3);

    if (sensorValue1 > 550)
    
    {
      Serial.println("");
      Serial.println("Water is A-okay on sensor 1! :D");
      digitalWrite(YLWLED, LOW);
    }

    if (sensorValue1 < 550)
    {
      Serial.println("");
      Serial.println("Need more water on sensor 1! D:");
      digitalWrite(YLWLED, HIGH);
    }
            
  Serial.print("Moisture Level 1 = " );                       
  Serial.println(sensorValue1);

  //Sensor 2


   if (sensorValue2 > 550)
    
    {
      Serial.println("");
      Serial.println("Water is A-okay on sensor 2! :D");
      digitalWrite(YLWLED, LOW);
    }

    if (sensorValue2 < 550)
    {
      Serial.println("");
      Serial.println("Need more water on sensor 2! D:");
      digitalWrite(YLWLED, HIGH);
    }
            
  Serial.print("Moisture Level 2 = " );                       
  Serial.println(sensorValue2);

  //Sensor 3

  if (sensorValue3 > 550)
    
    {
      Serial.println("");
      Serial.println("Water is A-okay on sensor 3! :D");
      digitalWrite(YLWLED, LOW);
    }

    if (sensorValue3 < 550)
    {
      Serial.println("");
      Serial.println("Need more water on sensor 3! D:");
      digitalWrite(YLWLED, HIGH);
    }
            
  Serial.print("Moisture Level 3 = " );                       
  Serial.println(sensorValue3);


  
  digitalWrite(ActivateSensor1, LOW);

   digitalWrite(ActivateSensor2, LOW);

    digitalWrite(ActivateSensor3, LOW);

    Serial.println("");
    Serial.println("");
  
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



     //BMP Pressure Sensor

    char status;
    double T,P,p0,a;

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


