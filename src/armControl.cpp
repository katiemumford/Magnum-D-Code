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

//for toggle between low/mid score
//0=low; 1=mid
int scoreLowOrMid = 0;

//for toggle between low/mid descore
//0=low; 1=mid
int descoreLowOrMid = 0;

//Y button toggles btwn 0 and 1 of scoreLowOrMid 
void toggleLowMidScore(){             
if (yPressed()){
  if (scoreLowOrMid == 0){
    scoreLowOrMid = 1;
  } else {
    scoreLowOrMid = 0;
  } }
}

//B button toggle btwn 0 and 1 of descoreLowOrMid
void toggleLowMidDescore(){             
if (bPressed()){
  if (descoreLowOrMid == 0){
    descoreLowOrMid = 1;
  } else {
    descoreLowOrMid = 0;
  } }
}

//when B pressed, brings arms to intake position
void armsToBase(){
  if (bPressed()){
    //lower arms until they get to limit switch
  }
}

//when A pressed




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

//READY TO BE TESTED ON A ROBOT --> IN THEORY, CAN CHECK CONTARMSTATE AND WHETHER PRESSING X DOES ANYTHING RIGHT
void testMe(){
   toggleLowMidScore();
   toggleLowMidDescore();
   armsToBase();
  if (aPressed()){
    Controller.Screen.print(descoreLowOrMid);
  } 
}

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
    testMe();  
    task::sleep(5);
  } return 1;
}