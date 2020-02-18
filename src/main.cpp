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

vex::controller Controller;

//drive base motor configs
vex::motor rF (vex::PORT10, false); //right front: port 10  --> correct, note motor facing backwards
vex::motor rB (vex::PORT4, false);  //right back: port 5    --> correct, note motor facing backwards
vex::motor lF (vex::PORT3, true);  //left front: 3         --> correct  
vex::motor lB (vex::PORT12, true);   //left back: 12       --> correct 

//intake motor config
vex::motor rin (vex::PORT13, true); //correct
vex::motor lin (vex::PORT9, false); //correct

//arm motor config
vex::motor arm (vex::PORT11, true); 

//tilter motor config (limit switch config declared robot-config.h and defined in robot-config.cpp)
vex::motor tray(vex::PORT14, true);                        


/////////////////////drive code////////////////////////////////////////////////////////////////

int minPct = 5; //minimum controller value (%) for drive, accounts for stick drift

void setDrive(double l, double r) { //voltage drive
  if (l < minPct && l > -minPct) { l = 0; }
  if (r < minPct && r > -minPct) { r = 0; } //accounts for stick drift
  l *= 12.0/100;
  r *= 12.0/100; //converts to volts

  lF.spin(vex::directionType::fwd, l, vex::voltageUnits::volt);
  lB.spin(vex::directionType::fwd, l, vex::voltageUnits::volt);
  rF.spin(vex::directionType::fwd, r, vex::voltageUnits::volt);
  rB.spin(vex::directionType::fwd, r, vex::voltageUnits::volt);
}

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
  vex::task controlArmsTask(armControl);


  while (1){ //always have a while, though if all your functions are tasks (which they should be) then this loop should be empty (note it should still be present)

    setDrive(Controller.Axis3.value()*100/127.0, Controller.Axis2.value()*100/127.0);
    intakeControl();
    armControl();
    trayControl();
    vex::task::sleep(20); 
  }
  
}
