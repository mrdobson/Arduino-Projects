#include <ArduinoRobot.h>

void setup(){
  Robot.begin();
}
void loop(){
  Robot.turn(90); //Make the robot turn 90 degrees right
  delay(1000);
}
