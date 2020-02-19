#include "vex.h"
using namespace vex;

//all tilter/tray related functions

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

int allowTrayForUser(){     //function that task calls
  while(true){
    trayControl(); 
    task::sleep(5);
  } return 1;
}