#include "vex.h"
using namespace vex;

bool buttonXPressed = false;
bool buttonYPressed = false;
bool buttonBPressed = false;
bool buttonAPressed = false;

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

  /*
else if (buttonNumber == 2){                  //2 --> Y
    if (Controller.ButtonY.pressing()){
      return 1;
    } else {
      return 0;
    }
  } 
  else if (buttonNumber == 3){                //3 --> A
    if (Controller.ButtonA.pressing()){
      return 1;
    } else {
      return 0;
    }
  }
  else if (buttonNumber == 4){                //4 --> B
    if (Controller.ButtonB.pressing()){
      return 1;
    } else {
      return 0;
    }
  }

  */
  
  
  
  