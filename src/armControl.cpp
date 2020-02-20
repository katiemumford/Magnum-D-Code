#include "vex.h"
using namespace vex;

//all arm related functions

/*
arms have three positions:
1) intake position         --> 0           
2) low twr                 --> 1
3) mid twr                 --> 2

plan: have three functions
1) changes value of int with a button press   changeStateNum()
2) checks the state of the arms               checksStateNum()
3) moves arms to state they need to be in     moveArmState()
--> use limit switch on arms to reset encoder of arm motor everytime they hit zero as well as limit in general
*/


int armState = 0; //physical location
int contArmState = 0; //where controller wants arms to go

//changes value of contArmState w/ button
void changeContArmState(){         
  if (contArmState != 2){    //checks if arms are in top state
    contArmState++;
  } else {
     contArmState = 0;   //if arms are in top, change to 0 to go down
  }
}

//when X pressed once, changes contArmState
void controllerChangeStateNum(){             
if (xPressed()){
  changeContArmState(); 
}
}

//move arm to low tower height
void moveArmToLowTwr(){
armState = 1;
}

//move arm to mid tower height
void moveArmToMidTwr(){
armState = 2;
}

//move arm to intake position
void moveArmToBase(){ 
if (armLimit.value() != 1){ 
  //
} else {
  armState = 0;
  arm.resetPosition();
}
}

//checks if need to move arm
void checkIfMoveArm(){    
  if (armState != contArmState){   //checks if physical arm location is different than the controller's
    if (contArmState == 1){
    moveArmToLowTwr();
  } else if (contArmState == 2){
    moveArmToMidTwr();
  } else if (contArmState == 0){
    moveArmToBase();
  }
   } else {    //arms are where controller wants them to be
     //default state; don't move arm at all or just down power type beat
  }
}

void macArmControl(){
  checkIfMoveArm(); 
}

//READY TO BE TESTED ON A ROBOT --> IN THEORY, CAN CHECK CONTARMSTATE AND WHETHER PRESSING X DOES ANYTHING RIGHT
void testMe(){
   controllerChangeStateNum();
  if (yPressed()){
    Controller.Screen.print(contArmState);
  }
}

//////////////////////classic manual arm code///////////////////////////
//adjustable function that moves arm to given percent value
//if given "0" will brake 
void moveArm(int pct) {     
  if (pct != 0) {
    arm.spin(vex::directionType::fwd, pct, vex::velocityUnits::pct);
  } else {
    arm.stop(vex::brakeType::brake);
  }
}

void manualArmControl() {   //code that moves   
if (Controller.ButtonX.pressing()){
  moveArm(-80);
} else if (Controller.ButtonB.pressing()){
  moveArm(80);
} else {
  moveArm(5);
}
}
////////////////////////////////////////////////////////////////////

int allowArmsForUser(){     //function that task calls
  while(true){
    //macArmControl(); 
    testMe();  
    task::sleep(5);
  } return 1;
}