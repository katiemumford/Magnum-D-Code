#include "vex.h"
using namespace vex;


const float voltConversion = 0.0944; 
int trayState = 0; //represents state of tray 0 = intake pos, 1 = defence pos, 2 = stack pos

//locations for positions 
float defensePos = -900;     //CHANGE/TUNE
float stackCheckPoint1 = 30;
float stackCheckPoint2 = 20;
float stackCheckPoint3 = -1700;


//helper method for spinning the tray at a given voltage speed
//takes trayPower and converts. so highest is 127 (12 in volts)
//*note* negative number moves tray towards from limit switch, positive brings it away from limit switch 
void moveTrayVolt(float trayPower){
  if (trayPower != 0){
    tray.spin(vex::directionType::fwd, double (trayPower * voltConversion), vex::voltageUnits::volt);
  } else {
    tray.stop(vex::brakeType::brake);
  }
}

//moves tray to intake position and resets encoder
void moveToIntakePos(){                   //if limit switch isn't hit (means tray isn't back yet) 
   if (trayLimit.value() != 1){      //move tray back until limit switch IS hit
      moveTrayVolt(-60);
      Controller.Screen.print("bruh");
   } else {
     moveTrayVolt(0);
     tray.resetPosition();
   }                      
}

//moves tray to defense pos
void moveToDefensePos(){              
  if ((-1*tray.position(deg)) > defensePos){
    moveTrayVolt(50);
  } else {
    moveTrayVolt(0);
  }
}

//moves tray to stacking pos
void moveToStackPos(){
  if (tray.position(deg) < stackCheckPoint1){
    moveTrayVolt(50);
  } else if (tray.position(deg) < stackCheckPoint2) {
    moveTrayVolt(40);
  } else if (tray.position(deg) < stackCheckPoint3){
    moveTrayVolt(20);
  } else {
    moveTrayVolt(0);
  }
}


void manualTray(){
  if (Controller.ButtonL2.pressing()){    //if L2 continously pressed, move tray towards limit switch
    if (trayLimit.value()!=1){ //if limit switch isn't hit move tray
      moveTrayVolt(-70);
    } else {
      moveTrayVolt(0);
    }                     
  } else if (Controller.ButtonL1.pressing()){    //if L1 continously pressed, move tray away from limit switch
    moveTrayVolt(70);
  } else{
    moveTrayVolt(0);
  }
}


void macroTrayControl(){
 switch(trayState){
    case 0:
      moveToIntakePos();    
      break;
    case 1:
      moveToDefensePos();
      break;
    case 2:
      moveToStackPos();
      break;
    case 3:
      manualTray();
    break;
}
}


void testMe(){

  macroTrayControl();

  if (aPressed()){   //get degrees for testing purposes
    Controller.Screen.print(trayState);
  }

  if (xPressed()){
    trayState = 0;
  }

  if (yPressed()){
    trayState = 1;
  }

  if (bPressed()){
    trayState = 2;
  }

  if (l1Pressed()){
    Controller.Screen.print(tray.position(deg));
  }

  if(l2Pressed()){
    trayState = 3;
  }

  }






int allowMacroTrayForUser(){  //function that task calls
  while(true){

    macroTrayControl();
    testMe();

    task::sleep(5);
  } return 1;
}