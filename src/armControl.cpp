#include "vex.h"
using namespace vex;

//all arm related functions

void moveArm(int pct) {   
  if (pct != 0) {
    arm.spin(vex::directionType::fwd, pct, vex::velocityUnits::pct);
  } else {
    arm.stop(vex::brakeType::brake);
  }
}

void armControl() {  
if (Controller.ButtonX.pressing()){
  moveArm(-80);
} else if (Controller.ButtonB.pressing()){
  moveArm(80);
} else {
  moveArm(5);
}
}

int allowArmsForUser(){     //function that task calls
  while(true){
    armControl(); 
    task::sleep(5);
  } return 1;
}