#include <HMC5883L.h>
#include <Wire.h>

HMC5883L compass; //Compass Library


void setup() {

  Serial.begin(9600);
  Wire.begin();

  compass = HMC5883L();
  setupHMC5883L();

}

void loop() {

  Serial.print("Compass: ");
  Serial.print(currentHeading);
  Serial.print("\t");

    else {
      //Case where the robot is pointing from 0-270 Deg
      if (currentHeading < 270)
      {
        //turn slightly right
        right();
      }

      //Case where the robot is pointing from 270-359 Deg
      if (currentHeading > 270)
      {
        //turn slightly left
        left();

      }
    }
}
