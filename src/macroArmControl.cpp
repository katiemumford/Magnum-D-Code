#include "vex.h"
using namespace vex;

//contains PLoooooop & code for arm toggles

//for toggle between 4 arm states
//represents the state of the arm at all times
int armState = 0;

const float kp = 0.89; //value that converts degrees to motor speed
const float voltConversion = 0.0944; //volt conversion for power
float error = 0; //difference between current and desired location
float armPower = 0; //motor speed found using loop
float targetValue = 0; //desired location

float derivative = 0; 
float kd = 0.32; 
float prevError = 0; 

float minPower = 40;
float maxPower = 120; 

//constantly running PLoop
void moveArmToHeight(int targetValue){  

error = (targetValue * -1) - arm.position(degrees);
derivative = error - prevError; 
prevError = error;

//converts error into motor speed
armPower = (error * kp) + (derivative * kd); 

//checks if overshooting max speed
if (armPower > maxPower){  
  armPower = maxPower;
} 

// motor spins at speed (voltage)
arm.spin(vex::directionType::fwd, (armPower * voltConversion), vex::voltageUnits::volt); 
}

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

void macroArmControl(){
switch(armState){
    case 0:
        targetValue = 0;
      //  Brain.Screen.printAt(10, 60, "base");  //apply continous down power eventually      
        break;
    case 1:
        //bring arms to low tower scoring height
        targetValue = 400;
       // Brain.Screen.printAt(10, 60, "score low twr");
        break;
    case 2:
       //  Brain.Screen.printAt(10, 60, "score mid twr");
         targetValue = 550;
        //bring arms to mid tower scoring height
        break;
    case 3:
        //bring arms to low tower descoring height
       // Brain.Screen.printAt(10, 60, "descore low twr");
        targetValue = 400;
        break;
    case 4:
        //bring arms to mid tower descoring height
       // Brain.Screen.printAt(10, 60, "descore mid twr");
        targetValue = 500;
        break;
}
}
void allowToggles(){
  toggleLowMidScore();
  toggleLowMidDescore();
  armsToBase();
}

int allowMacroArmsForUser(){   //function that task calls
  while (true){
   
  //if (manualMovingg == false){         //checks that arms aren't moving  *work in progress, prob will just add another state*
    macroArmControl();
    moveArmToHeight(targetValue);
    allowToggles();
  //  }
 
 // for testing P loop
  Brain.Screen.printAt(10, 60, "degrees %lf", arm.position(degrees));
  Brain.Screen.printAt(10, 80, "target value %f", targetValue);
  Brain.Screen.printAt(10, 100, "error %f", error);
  Brain.Screen.printAt(10, 120, "power %f", armPower);

  task::sleep(5);
  } 
  return 1;
}