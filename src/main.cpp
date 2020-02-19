/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       KatieMumford                                              */
/*    Created:      Sun Feb 16 2020                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
using namespace vex;
 
///////////////////////arm code//////////////////////////////////////////////////////////////////

void moveArm(int pct) {   
  if (pct != 0) {
    arm.spin(vex::directionType::fwd, pct, vex::velocityUnits::pct);
  } else {
    arm.stop(vex::brakeType::brake);
  }
}

int armControl() {  
if (Controller.ButtonX.pressing()){
  moveArm(-80);
} else if (Controller.ButtonB.pressing()){
  moveArm(80);
} else {
  moveArm(5);
}
return 1;
}

/////////////////intake code//////////////////////////////////////////////////////////////////////

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

///////////////////////tray code//////////////////////////////////////////////////////////////////

void moveTray(int pct) {
  if (pct!= 0) {
      tray.spin(vex::directionType::fwd, pct, vex::velocityUnits::pct);
  } else {
    tray.stop(vex::brakeType::brake);
  } 
}

void trayControl() {

  if (Controller.ButtonL2.pressing()){    //if L2 continously pressed, move tray towards limit switch
    if (trayLimit.value()==1){
      moveTray(0);
    } else {
      moveTray(-70);
    }                     
  } else if (Controller.ButtonL1.pressing()){    //if L1 continously pressed, move tray away from limit switch
    moveTray(20);
  } else{
    moveTray(0);
  }
}

void limitTest(){  //tests if limit switch works. it does. 
  if(trayLimit.value() == 1){
    Controller.Screen.print("I was pressed");
  }
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*task notes

declare and define a task in the main. use this --> vex::task taskName(functionTaskCalls);
the function a task calls must be an int, meaning the function must return an int. which, we don't always want. in that case, you can put everything you need in a while that's always true

*/

int main() {  //beginning of code

// Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();


  vex::task allowsTankDriveForUserTask(drive);
  //vex::task controlArmsTask(armControl);


  while (1){ //always have a while, though if all your functions are tasks (which they should be) then this loop should be empty (note it should still be present)

    intakeControl();
    armControl();
    trayControl();
    vex::task::sleep(20); 
  }
  
}
