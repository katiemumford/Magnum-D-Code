#include "vex.h"
using namespace vex;

const float voltConversion = 0.0944; 
int trayState; //represents state of tray 0 = intake pos, 1 = defence pos, 2 = stack pos

//locations for positions 
float defensePos = 40;     //CHANGE/TUNE
float stackCheckPoint1 = 30;
float stackCheckPoint2 = 20;
float stackCheckPoint3 = 10;


//helper method for spinning the tray at a given voltage speed
//takes trayPower and converts. so highest is 127 (12 in volts)
void moveTrayVolt(float trayPower){
  if (trayPower != 0){
    tray.spin(vex::directionType::fwd, double (trayPower * voltConversion), vex::voltageUnits::volt);
  } else {
    tray.stop(vex::brakeType::brake);
  }
}




//moves tray to intake position and resets encoder
void moveToIntakePos(){
  if (trayLimit.value() != 1){           //if limit switch isn't hit (means tray isn't back yet) 
    while (trayLimit.value() != 1){      //move tray back until limit switch IS hit
      moveTrayVolt(100);
    }
  } else {
    moveTrayVolt(0);                  //if limit switch is hit, means tray all the way back, so don't spin motor
    tray.resetPosition();             //reset encoder of motor for greater accuracy for future use
  }
}

//moves tray to defense pos
void moveToDefensePos(){              
  if (tray.position(deg) < defensePos){
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


void macroTrayControl(){
 switch(trayState){
    case 0:
      moveToIntakePos();
      //Brain.Screen.printAt(10, 60, "base");  //apply continous down power eventually      
      break;
    case 1:
       moveToDefensePos();
       // Brain.Screen.printAt(10, 60, "score low twr");
      break;
    case 2:
      moveToStackPos();
       //Brain.Screen.printAt(10, 60, "score mid twr");
      break;
}
}

void testMe(){

  if (Controller.ButtonL2.pressing()){    //if L2 continously pressed, move tray towards limit switch
    if (trayLimit.value()!=1){ //if limit switch isn't hit move tray
      moveTrayVolt(-70);
    } else {
      moveTrayVolt(0);
    }                     
  } else if (Controller.ButtonL1.pressing()){    //if L1 continously pressed, move tray away from limit switch
    moveTrayVolt(20);
  } else{
    moveTrayVolt(0);
  }
  }






int allowMacroTrayForUser(){  //function that task calls
  while(true){

    testMe();

    task::sleep(5);
  } return 1;
}