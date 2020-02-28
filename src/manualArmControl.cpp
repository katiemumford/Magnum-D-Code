#include "vex.h"
using namespace vex;

//all arm related functions






/////////////////////////////////////////////////////////////////

//adjustable function that moves arm to given percent value
//if given "0" will brake 
void moveArm(int pct) {     
  if (pct != 0) {
    arm.spin(vex::directionType::fwd, pct, vex::velocityUnits::pct);
  } else {
    arm.stop(vex::brakeType::brake);
  }
}

void manualArmControl() {              //code that moves arms manually 
if (Controller.ButtonUp.pressing()){
  manualMovingg = true;
  moveArm(-80);
} else if (Controller.ButtonDown.pressing()){
  manualMovingg = true;
  moveArm(80);
} else {
  moveArm(0); 
}
}
////////////////////////////////////////////////////////////////////

int allowManualArmsForUser(){     //function that task calls
  while(true){
    manualArmControl(); 
    task::sleep(5);
  } return 1;
}