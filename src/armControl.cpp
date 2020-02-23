#include "vex.h"
using namespace vex;

//all arm related functions

/*
arms have three positions:
1) intake position         --> 0           
2) low twr                 --> 1
3) mid twr                 --> 2

plan: have three functions
1) changes value of int with a button press 
2) checks the state of the arms               
3) 3 functions that move arms to state they need to be in   

--> use limit switch on arms to reset encoder of arm motor everytime they hit zero as well as limit in general
*/

  /* first draft with all cases. currently commented out to testing simplicity 
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
  }//physical location
int armState = 0; 
//where controller wants arms to go
int contArmState = 0; 


//move arm to intake position
void moveArmToBase(){
  Controller.Screen.print("base");
  armState = 0;
}

//move arm to low tower height
void moveArmToLowTwr(){
  Controller.Screen.print("low");
  armState = 1;
}

//move arm to mid tower height
void moveArmToMidTwr(){
  Controller.Screen.print("mid");
  armState = 2;
}

//checks if need to move arm
void checkIfMoveArm(){ 
  if (armState != contArmState){
    if (contArmState==0){
      moveArmToBase();
    } else if(contArmState==1){
      moveArmToLowTwr();
    } else if (contArmState==2){
      moveArmToMidTwr();
    }
  } //add an else for do nothing later
 
}


//changes value of contArmState w/ button                     
//if arms aren't in top state, +1 to contArmState
//if arms are in top, change contArmState to 0 (go to base)

void changeContArmState(){         
  if (contArmState != 2){    
    contArmState++;
  } else {
     contArmState = 0;   
  }
}

//when X pressed once, changes contArmState
void controllerChangeStateNum(){             
if (xPressed()){
  changeContArmState(); 
}
}

  */ 

//////////////////////classic manual arm code/////////////////////////

//adjustable function that moves arm to given percent value
//if given "0" will brake 
void moveArm(int pct) {     
  if (pct != 0) {
    arm.spin(vex::directionType::fwd, pct, vex::velocityUnits::pct);
  } else {
    arm.stop(vex::brakeType::brake);
  }
}

void manualArmControl() {              //code that moves   
if (Controller.ButtonX.pressing()){
  moveArm(-80);
} else if (Controller.ButtonB.pressing()){
  moveArm(80);
} else {
  moveArm(5); //we found 5 works nice 
}
}
////////////////////////////////////////////////////////////////////

int allowArmsForUser(){     //function that task calls
  while(true){
    manualArmControl(); 
    task::sleep(5);
  } return 1;
}