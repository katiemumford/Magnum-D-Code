#include "vex.h"
using namespace vex;

//all intake related functions

void spinIntake(int pct) {
  if (pct != 0) {
    rin.spin(vex::directionType::fwd, pct, vex::velocityUnits::pct);
    lin.spin(vex::directionType::fwd, pct, vex::velocityUnits::pct);
  } else {
    rin.stop(vex::brakeType::brake);
    lin.stop(vex::brakeType::brake);
  }
}

void intakeControl() {
  if (Controller.ButtonR1.pressing()){
    spinIntake(100);
  } else if (Controller.ButtonR2.pressing()){
    spinIntake(-100);
  } else {
    spinIntake(5);
  }
}

int allowIntakeForUser(){     //function that task calls
  while(true){
    intakeControl(); 
    task::sleep(5);
  } return 1;
}