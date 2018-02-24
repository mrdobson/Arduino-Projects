//Sensor LEDs
  int Sensor1LED = 22;
  int Sensor2LED = 24;
  int Sensor3LED = 26;
  int Sensor4LED = 28;
  int Sensor5LED = 30;

  int IRsensorPin1 = A8; //IR 1
  int IRsensorPin2 = A9; //IR 2
  int IRsensorPin3 = A10; //IR 3
  int IRsensorPin4 = A11; //IR 4
  int IRsensorPin5 = A12; //IR 5

  int IRsensorValue1 = 0; //Integer value from IR 1
  int IRsensorValue2 = 0; //Integer value from IR 2
  int IRsensorValue3 = 0; //Integer value from IR 3
  int IRsensorValue4 = 0; //Integer value from IR 4
  int IRsensorValue5 = 0; //Integer value from IR 5

  int ObstacleSeen = 500;  //Middle Obstacle
  int LeftObstruction = 500;  //Left Obstacle
  int RightObstruction = 500;  //Right Obstacle
  int LeftPass = 500;  //Left Clear
  int RightPass = 500;  //Right Clear

void setup() {

  Serial.begin(9600);

    //Input pins
    pinMode(IRsensorPin1, INPUT); //Reading from IR 1
    pinMode(IRsensorPin2, INPUT); //Reading from IR 2
    pinMode(IRsensorPin3, INPUT); //Reading from IR 3
    pinMode(IRsensorPin4, INPUT); //Reading from IR 4
    pinMode(IRsensorPin5, INPUT); //Reading from IR 5

 

    pinMode(Sensor1LED, OUTPUT);
    pinMode(Sensor2LED, OUTPUT);
    pinMode(Sensor3LED, OUTPUT);
    pinMode(Sensor4LED, OUTPUT);
  

}

void loop() {

  //turn all leds off at beginning of loop
  digitalWrite(Sensor1LED, LOW);    //forwards
  digitalWrite(Sensor2LED, LOW);   //backwards
  digitalWrite(Sensor3LED, LOW);      //right
  digitalWrite(Sensor4LED, LOW);       //left
  digitalWrite(Sensor5LED, LOW);  

      IRsensorValue1 = analogRead(IRsensorPin1);
      IRsensorValue2 = analogRead(IRsensorPin2);
      IRsensorValue3 = analogRead(IRsensorPin3);
      IRsensorValue4 = analogRead(IRsensorPin4);
      IRsensorValue5 = analogRead(IRsensorPin5);

    Serial.print("IR Reading Middle: ");
    Serial.print(IRsensorValue1);
    Serial.print("\n");
    Serial.print("\n");

    Serial.print("IR Reading Front Left: ");
    Serial.print(IRsensorValue2);
    Serial.print("\n");
    Serial.print("\n");
  
    Serial.print("IR Reading Front Right: ");
    Serial.print(IRsensorValue3);
    Serial.print("\n");
    Serial.print("\n");
  
    Serial.print("IR Reading Back Left: ");
    Serial.print(IRsensorValue4);
    Serial.print("\n");
    Serial.print("\n");
  
    Serial.print("IR Reading Back Right: ");
    Serial.print(IRsensorValue5);
    Serial.print("\n");
    Serial.print("\n");

  delay(300);

  // Check IR Sensor. If it is too close to something take evasive maneuvers
    if (IRsensorValue1 > ObstacleSeen)
    {

      //evasive maneuvers
      Serial.println("");
      Serial.println("Danger!!  Object detected!");
      digitalWrite(Sensor1LED, HIGH);
      delay(50);
    }
    
    if (IRsensorValue2 > LeftObstruction)
    {

      Serial.println("");
      Serial.println("Danger!!  Object detected!");
      digitalWrite(Sensor2LED, HIGH);
      delay(50);
    }

    if (IRsensorValue3 > RightObstruction)
    {

      Serial.println("");
      Serial.println("Danger!!  Object detected!");
      digitalWrite(Sensor3LED, HIGH);
      delay(50);
    }
    
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

}

