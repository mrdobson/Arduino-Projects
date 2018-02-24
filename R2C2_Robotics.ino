

#include <Wire.h>
#include <HMC5883L.h>

HMC5883L compass;

#define fio 0x08

int headingError = 10;
int headingGoal; 
int headingMax;
int headingMin;

float headingDegrees = 0;

//A is the Right Wheel and B is the Left Wheel
int pwm_a = 3;   // Right Wheel Speed
int pwm_b = 11;  // Left Wheel Speed
int dir_a = 12;  // Right Wheel Direction
int dir_b = 13;  // Left Wheel Direction

int movingPin = 8;       //Enable movement of the robot.  Low for sensor/Serial work, High moving around (Movement Enabled)

int RightWheelTurn = 200;  // The speed of the right wheel turning
int LeftWheelTurn = 200;   // The speed of the left wheel turning

int SpeedOfRightWheel = 100;  // Right and left wheel normal speed
int SpeedOfLeftWheel = 100;

//Sensor LEDs
  int Sensor1LED = 22;
  int Sensor2LED = 24;
  int Sensor3LED = 26;
  int Sensor4LED = 28;
  int Sensor5LED = 30;

//Sensor Pins
  int IRsensorPin1 = A8;  //IR 1
  int IRsensorPin2 = A9;  //IR 2
  int IRsensorPin3 = A10; //IR 3
  int IRsensorPin4 = A11; //IR 4
  int IRsensorPin5 = A12; //IR 5

//Declare Sensor Value
  int IRsensorValue1 = 0; //Integer value from IR 1
  int IRsensorValue2 = 0; //Integer value from IR 2
  int IRsensorValue3 = 0; //Integer value from IR 3
  int IRsensorValue4 = 0; //Integer value from IR 4
  int IRsensorValue5 = 0; //Integer value from IR 5

//Obstruction Definitions
  int ObstacleSeen = 500;         // Middle Obstacle
  int LeftObstruction = 500;      // Left Obstacle
  int RightObstruction = 500;     // Right Obstacle
  int LeftPass = 500;             // Left Clear
  int RightPass = 500;            // Right Clear

void setup() {

  //Compass

  Serial.begin(9600);

  // Initialize HMC5883L
  Serial.println("Initialize HMC5883L");
  while (!compass.begin())
  {
    Serial.println("Could not find a valid HMC5883L sensor, check wiring!");
    delay(500);
  }

  // Set measurement range
  compass.setRange(HMC5883L_RANGE_1_3GA);

  // Set measurement mode
  compass.setMeasurementMode(HMC5883L_CONTINOUS);

  // Set data rate
  compass.setDataRate(HMC5883L_DATARATE_30HZ);

  // Set number of samples averaged
  compass.setSamples(HMC5883L_SAMPLES_8);

  // Set calibration offset. See HMC5883L_calibration.ino
  compass.setOffset(0, 0);

  //Declare Motor Outputs
    pinMode(pwm_a, OUTPUT);      // Right Motors
    pinMode(pwm_b, OUTPUT);      // Left Motors
    pinMode(dir_a, OUTPUT);      // Right Direction
    pinMode(dir_b, OUTPUT);      // Left Direction
    
  //Begin Motors at 0 speed
    analogWrite(pwm_a, 0);          
    analogWrite(pwm_b, 0);

  //Input pins
    pinMode(IRsensorPin1, INPUT);   // Reading from IR 1
    pinMode(IRsensorPin2, INPUT);   // Reading from IR 2
    pinMode(IRsensorPin3, INPUT);   // Reading from IR 3
    pinMode(IRsensorPin4, INPUT);   // Reading from IR 4
    pinMode(IRsensorPin5, INPUT);   // Reading from IR 5

  //Activate Each LED
    pinMode(Sensor1LED, OUTPUT);
    pinMode(Sensor2LED, OUTPUT);
    pinMode(Sensor3LED, OUTPUT);
    pinMode(Sensor4LED, OUTPUT);
    pinMode(Sensor5LED, OUTPUT);

}

void loop() {

   getCompass();
   beaconHeading();
   headingGoal = 280;
   headingMaximum();
   headingMinimum();
   
    // Sketchy switch
    /*if (digitalRead(movingPin) == 0)
    {
      
      // turn the motors off
        analogWrite(pwm_a, 0);  //set both motors to run at 0% duty cycle (off)
        analogWrite(pwm_b, 0);
      
      //wait
        Serial.println("motors off");
          delay(1000);
    }
      /*Mobility Test Lines
      forward();
        delay(5000);
      backward();
        delay(5000);
      right();
        delay(5000);
      left();
        delay(5000);  */
      
        
  // LED Start
  // turn all leds off at beginning of loop
      digitalWrite(Sensor1LED, LOW);        //Middle
      digitalWrite(Sensor2LED, LOW);        //Left
      digitalWrite(Sensor3LED, LOW);        //Right
      digitalWrite(Sensor4LED, HIGH);        //Clear Left
      digitalWrite(Sensor5LED, HIGH);        //Clear Right

      IRsensorValue1 = analogRead(IRsensorPin1);
      IRsensorValue2 = analogRead(IRsensorPin2);
      IRsensorValue3 = analogRead(IRsensorPin3);
      IRsensorValue4 = analogRead(IRsensorPin4);
      IRsensorValue5 = analogRead(IRsensorPin5);

  //Basic Movement

  if((headingMin<=headingDegrees) && (headingDegrees<=headingMax))
  {
  forward();
  delay(250);
  }

  if(headingMin > headingDegrees)
  {
  right();
  delay(250);
  }

  if(headingMax < headingDegrees)
  {
  left();
  delay(250);
  }

  // Determine if the robot should move ("1") or if it should stay still ("0")
  // First case, moving pin == 0. Robot does not move.  movingPin is set to 0V.
  
  {
    
    if (IRsensorValue1 > ObstacleSeen)
    {
      //evasive maneuvers
      
      digitalWrite(Sensor1LED, HIGH);
      int Obstacle = 1;
      delay(50);
    }
    
    if (IRsensorValue2 > LeftObstruction)
    {
      digitalWrite(Sensor2LED, HIGH);
      int Obstacle = 2;
      delay(50);
    }

    if (IRsensorValue3 > RightObstruction)
    {
      digitalWrite(Sensor3LED, HIGH);
      int Obstacle = 3;
      delay(50);
    }

  } 
}

//End Obstruction Detection

   // Not worrying about this yet
   /* else {
      
    
      if (IRsensorValue4 > LeftPass)
      {
      Serial.println("");
      Serial.println("We're clear on left!");
      digitalWrite(Sensor4LED, HIGH);
        delay(50);
      }

      if (IRsensorValue5 > RightPass)
      {
      Serial.println("");
      Serial.println("We're clear on right!");
      digitalWrite(Sensor5LED, HIGH);
        delay(50);
      } 
      
      //Case where the robot is pointing from 0-270 Deg
      if (currentHeading < 270)
      {
        //turn slightly right
        right();
      }
      
    } */



void forward()
{
    
  digitalWrite(dir_a, HIGH);
  digitalWrite(dir_b, HIGH);
  analogWrite(pwm_a, SpeedOfRightWheel);
  analogWrite(pwm_b, SpeedOfLeftWheel);
}


void backward()
{
  digitalWrite(dir_a, LOW);
  digitalWrite(dir_b, LOW);
  analogWrite(pwm_a, SpeedOfRightWheel);
  analogWrite(pwm_b, SpeedOfLeftWheel);
}


void left()
{
  digitalWrite(dir_a, HIGH);
  digitalWrite(dir_b, LOW);
  analogWrite(pwm_a, RightWheelTurn);
  analogWrite(pwm_b, LeftWheelTurn);  // Forward Right, Backward Left
}

void right()
{
  digitalWrite(dir_a, LOW);
  digitalWrite(dir_b, HIGH);
  analogWrite(pwm_a, RightWheelTurn);
  analogWrite(pwm_b, LeftWheelTurn);  // Forward Left, Backward Right
}

void getCompass(){
  Vector norm = compass.readNormalize();

  // Calculate heading
  float heading = atan2(norm.YAxis, norm.XAxis);

  // Set declination angle on your location and fix heading
  // You can find your declination on: http://magnetic-declination.com/
  // (+) Positive or (-) for negative
  // For Bytom / Poland declination angle is 4'26E (positive)
  // Formula: (deg + (min / 60.0)) / (180 / M_PI);
  float declinationAngle = (8.0 + (4.0 / 60.0)) / (180 / M_PI);
  heading += declinationAngle;

  // Correct for heading < 0deg and heading > 360deg
  if (heading < 0)
  {
    heading += 2 * PI;
  }

  if (heading > 2 * PI)
  {
    heading -= 2 * PI;
  }

  // Convert to degrees
  float headingDegrees = heading * 180/M_PI; 

  // Output
  Serial.print(" Heading = ");
  Serial.print(heading);
  Serial.print(" Degress = ");
  Serial.print(headingDegrees);
  Serial.println();
}

void beacon()
{
  Wire.requestFrom(fio, 2);    // request 6 bytes from slave device #8
  Serial.print("Heading:  ");
  Serial.println(beaconHeading());
}

int beaconHeading()
{
  Wire.requestFrom(fio, 2);    // request 6 bytes from slave device #8
  byte MSB = Wire.read();
  byte LSB = Wire.read();
  return (MSB<<8)|LSB;
}

void headingMaximum(){
  if((headingGoal+headingError)>360)
  {
    headingMax = ((headingGoal+headingError)-360);
  }
  else{
    headingMax = (headingGoal+headingError);
  }
}

void headingMinimum(){
  if((headingGoal-headingError)<=0)
  {
    headingMin = ((headingGoal-headingError)+360);
  }
  else{
    headingMin = (headingGoal-headingError);
  }
 }
