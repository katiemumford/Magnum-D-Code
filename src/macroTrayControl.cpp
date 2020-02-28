#include "vex.h"
using namespace vex;

//generic info: tray control task that allows user to use three macros to move tray between intake, defense, stack pos
//CURRENTLY: L1 toggles between intake pos and defence pos
//L2 places the stack
//Left button enables manual control with L1 going foward and L2 going back. stays this way until other button pressed


//represents state of tray 0 = intake pos, 1 = defence pos, 2 = stack pos
int trayState = 0; 
const float voltConversion = 0.0944; 


//locations for positions 
float defensePos = -900;     
float stackCheckPoint1 = -930;
float stackCheckPoint2 = -1200;
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
void moveToIntakePos(){            
   if (trayLimit.value() != 1){           
      moveTrayVolt(-60);
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
  if ((-1 * tray.position(deg)) > stackCheckPoint1){
    moveTrayVolt(50);
  } else if ((-1 * tray.position(deg)) > stackCheckPoint2) {
    moveTrayVolt(30);
  } else if ((-1 * tray.position(deg)) > stackCheckPoint3){
    moveTrayVolt(20);
  } else {
    moveTrayVolt(0);
  }
}

//L1 button toggles btwn 1 and 2 of armState 
void toggleIntakeDefense(){             
if (l1Pressed()){
  if (trayState == 0){
    trayState = 1;
  } else {
    trayState = 0;
  } }
}

//L2 button pressed changes armState to 2 (place stack)
void placeStack(){
  if (l2Pressed()){
    trayState = 2;
  }
}

//Left button pressed changes armState to 3 (switch to manual trayControl)
void enableManual(){
  if (leftPressed()){
    trayState = 3;
  }
}

//if L2 pressed move tray towards limit switch
//if L1 pressed move tray away from limit switch
void manualTray(){
  if (Controller.ButtonL2.pressing()){    
    if (trayLimit.value()!=1){          
      moveTrayVolt(-70);
    } else {
      moveTrayVolt(0);
    }                     
  } else if (Controller.ButtonL1.pressing()){    
    moveTrayVolt(70);
  } else{
    moveTrayVolt(0);
  }
}

//switch statement that calls tray movement functions depending on trayState value
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

  //prints trayState for testing purposes if A button is pressed  (not compatable with armControl task)
  if (aPressed()){  
    Controller.Screen.print(trayState);
  }

  //prints tray degrees for testing purposes if X is pressed (not compatable with armControl task) 
  if (xPressed()){
    Controller.Screen.print(tray.position(deg));
  }

  }


int allowMacroTrayForUser(){  //function that task calls
  while(true){

    macroTrayControl();
    testMe();

    task::sleep(5);
  } return 1;
}