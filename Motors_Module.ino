//A is the Right Wheel and B is the Left Wheel
int pwm_a = 3;   // Right Wheel Speed
int pwm_b = 11;  // Left Wheel Speed
int dir_a = 12;  // Right Wheel Direction
int dir_b = 13;  // Left Wheel Direction


int speedOfRightWheel = 150;  // The speed of the right wheel
int speedOfLeftWheel = 150;   // The speed of the left wheel


void setup() {

  pinMode(pwm_a, OUTPUT);      //Set motor control pins to be outputs from the Arduino
  pinMode(pwm_b, OUTPUT);
  pinMode(dir_a, OUTPUT);
  pinMode(dir_b, OUTPUT);

  analogWrite(pwm_a, 0);          //set both motors speed to 0% duty cycle (off)
  analogWrite(pwm_b, 0);
}

void loop() {
  //Determine if the robot should move ("1") or if it should stay still ("0")
  // First case, moving pin == 0. Robot does not move.  movingPin is set to 0V.

forward();
}

void forward()
{
  Serial.println("Forward");
  digitalWrite(dir_a, HIGH);
  digitalWrite(dir_b, HIGH);
  analogWrite(pwm_a, speedOfRightWheel);
  analogWrite(pwm_b, speedOfLeftWheel);
  
}




void backward()
{
  Serial.println("Backward");
  digitalWrite(dir_a, LOW);
  digitalWrite(dir_b, LOW);
  analogWrite(pwm_a, speedOfRightWheel);
  analogWrite(pwm_b, speedOfLeftWheel);
  
}


void left()
{
  Serial.println("Left Turn");
  digitalWrite(dir_a, HIGH);
  digitalWrite(dir_b, LOW);
  analogWrite(pwm_a, speedOfRightWheel);
  analogWrite(pwm_b, speedOfLeftWheel);  //spin the left wheel slower so the robot turns left
  
}

void right()
{
  Serial.println("Right Turn");  
  digitalWrite(dir_a, LOW);
  digitalWrite(dir_b, HIGH);
  analogWrite(pwm_a, speedOfRightWheel); //spin the right wheel slower so the robot turns right
  analogWrite(pwm_b, speedOfLeftWheel);
  
}
