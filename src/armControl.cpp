#include "vex.h"
using namespace vex;

//all arm related functions


////////////////////state machine type beat
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


int armState = 0; 
int contArmState = 0; 

void changeStateNum(){        //changes value of contArmState. used by controller when button a is pressed 
Controller.Screen.print(armState);  //4:00 weds, this function was entered after B was pressed
  if (contArmState == 2){    //checks if arms are in top state and will change 
    //contArmState = 0;
    Controller.Screen.print("in if"); // keeps entering here for some reason
  } else {
     Controller.Screen.print("in else");
     contArmState++;   //if at else, then it means arms can go up by one and will be increased accordingly
  }
}


////////////test printing/////////////////////



int count = 0;
void testMe(){

if (xPressed()){
  Controller.Screen.print("suck");
}
if (yPressed()){
  Controller.Screen.print("my");
}
if (bPressed()){
  Controller.Screen.print("dick");
}
if (aPressed()){
  Controller.Screen.print("james!");
}
// if (getButton(2)==1){
//   count = 1; 
// }
// if (getButton(3)==1){
//   Controller.Screen.clearScreen();
//   Controller.Screen.print("Cleaning time");
// }
}



////////////////////////////////



void controllerChangeStateNum(){              //changes value of int with button press
Controller.ButtonB.pressed(changeStateNum);  //when button a is pressed it will change the value of contArmState
}



void moveArmToLowTwr(){
//move arm to low tower height
armState = 1;
}

void moveArmToMidTwr(){
//move arm to mid tower height
armState = 2;
}

void moveArmToBase(){
//move arm to intake position 
armState = 0;
}

void checkIfMoveArm(){    //checks if the arm state is the same or if it needs to change
  if (armState == contArmState){   //
    //arm do nothing, lock, stay where it is
  } else { //check which functions to call
  if (contArmState == 1){
    moveArmToLowTwr();
  } else if (contArmState == 2){
    moveArmToMidTwr();
  } else if (contArmState == 0){
    moveArmToBase();
  }
  }
}

////////////////////////////////////////////////////////////////////

void moveArm(int pct) {    //adjustable function that moves arm to given percent value 
  if (pct != 0) {
    arm.spin(vex::directionType::fwd, pct, vex::velocityUnits::pct);
  } else {
    arm.stop(vex::brakeType::brake);
  }
}

void armControl() {   //code that moves   
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
    //armControl();     //commented arm control out to test if incrementing works
  
    testMe();

    task::sleep(5);
  } return 1;
}