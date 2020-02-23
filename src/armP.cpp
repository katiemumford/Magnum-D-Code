#include "vex.h"
using namespace vex;

//error = target - sensor value (arm motor encoder's degree amount)
//speed = error

const float kp = 0.3; //value that converts degrees to motor speed
const float voltConversion = 0.0944;
int error = 0; //difference between where we want to be and where we are
int armPower = 0; //motor speed found using loop
int targetValue = 0;

void moveArmToHeight(int targetValue){  //P loop

error = (targetValue * -1) - arm.position(degrees); // error equals target minus current arm position
armPower = error * kp; //converts error into motor speed

arm.spin(vex::directionType::fwd, (armPower * voltConversion), vex::voltageUnits::volt); // motor spins at speed (voltage)
 
}

//for toggle between 4 arm states
//represents the state of the arm at all times
int armState = 0;

//Y button toggles btwn 1 and 2 of scoreHeight 
void toggleLowMidScore(){             
if (yPressed()){
  if (armState == 1){
    armState = 2;
  } else {
    armState = 1;
  } }
}

//B button toggle btwn 3 and 4 of descoreHeight
void toggleLowMidDescore(){             
if (bPressed()){
  if (armState == 3){
    armState = 4;
  } else {
    armState = 3;
  } }
}

//when X pressed, brings arms to intake position
void armsToBase(){
  if (xPressed()){
    armState = 0;
  }
}

void allowToggle(){
  toggleLowMidScore();
  toggleLowMidDescore();
  armsToBase();
}

void macroArmControl(){
switch(armState){
    case 0:
        //bring arms to base
        Brain.Screen.printAt(10, 60, "base");        
        break;
    case 1:
        //bring arms to low tower scoring height
        //Controller.Screen.print("lowtwr.score"); 
        Brain.Screen.printAt(10, 60, "score low twr");
        break;
    case 2:
        //bring arms to mid tower scoring height
        //Controller.Screen.print("midtwr.score"); 
        Brain.Screen.printAt(10, 60, "score mid twr");
        break;
    case 3:
        //bring arms to low tower descoring height
        //Controller.Screen.print("lowtwr.descore");
        Brain.Screen.printAt(10, 60, "descore low twr");
        break;
    case 4:
        //bring arms to mid tower descoring height
        //Controller.Screen.print("midtwr.descore");
        Brain.Screen.printAt(10, 60, "descore mid twr");
        break;
}
}

void whatIsArmState(){
  if (aPressed()){
    Controller.Screen.print(armState);
  }
}

int allowPForUser(){   //function that task calls
  while (true){

    macroArmControl();
    moveArmToHeight(targetValue);
    whatIsArmState();
    allowToggle();
    


  /*  for testing P loop
  Brain.Screen.printAt(10, 60, "degrees %f", arm.position(degrees));
  Brain.Screen.printAt(10, 80, "target value %f", targetValue);
  Brain.Screen.printAt(10, 100, "error %f", error);
  Brain.Screen.printAt(10, 120, "power %f", armPower);
  */

  task::sleep(5);
  } 
  return 1;
}