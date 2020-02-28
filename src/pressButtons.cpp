#include "vex.h"
using namespace vex;

bool buttonXPressed = false;
bool buttonYPressed = false;
bool buttonBPressed = false;
bool buttonAPressed = false;
bool buttonUpPressed = false;
bool buttonDownPressed = false;
bool buttonL1Pressed = false;
bool buttonL2Pressed = false;

int xPressed(){                
    if (Controller.ButtonX.pressing()){
    if (!buttonXPressed){
      buttonXPressed = true;
      return 1;
    }
    } if (!Controller.ButtonX.pressing()){
      buttonXPressed = false;
    }
    return 0; 
}

int yPressed(){                
    if (Controller.ButtonY.pressing()){
    if (!buttonYPressed){
      buttonYPressed = true;
      return 1;
    }
    } if (!Controller.ButtonY.pressing()){
      buttonYPressed = false;
    }
    return 0; 
}

int bPressed(){                
    if (Controller.ButtonB.pressing()){
    if (!buttonBPressed){
      buttonBPressed = true;
      return 1;
    }
    } if (!Controller.ButtonB.pressing()){
      buttonBPressed = false;
    }
    return 0; 
}

int aPressed(){                
    if (Controller.ButtonA.pressing()){
    if (!buttonAPressed){
      buttonAPressed = true;
      return 1;
    }
    } if (!Controller.ButtonA.pressing()){
      buttonAPressed = false;
    }
    return 0; 
}

int upPressed(){
  if (Controller.ButtonUp.pressing()){
    if (!buttonUpPressed){
      buttonUpPressed = true;
      return 1;
    }
    } if (!Controller.ButtonUp.pressing()){
      buttonUpPressed = false;
    }
    return 0;
}

int downPressed(){
  if (Controller.ButtonDown.pressing()){
    if (!buttonDownPressed){
      buttonDownPressed = true;
      return 1;
    }
    } if (!Controller.ButtonDown.pressing()){
      buttonDownPressed = false;
    }
    return 0;
}

int l1Pressed(){
  if (Controller.ButtonL1.pressing()){
    if (!buttonL1Pressed){
      buttonL1Pressed = true;
      return 1;
    }
    } if (!Controller.ButtonL1.pressing()){
      buttonL1Pressed = false;
    }
    return 0;
}

int l2Pressed(){
  if (Controller.ButtonL2.pressing()){
    if (!buttonL2Pressed){
      buttonL2Pressed = true;
      return 1;
    }
    } if (!Controller.ButtonL2.pressing()){
      buttonL2Pressed = false;
    }
    return 0;
} 