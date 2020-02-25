/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       KatieMumford                                              */
/*    Created:      Sun Feb 16 2020                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
using namespace vex;

/*/////INFORMATION/////
THIS IS WHERE YOUR MAIN FUNCTION IS
-where you define tasks and run auton
*/

/*task notes
declare and define a task in the main. use this --> vex::task taskName(functionTaskCalls);
the function a task calls must be an int, meaning the function must return an int. which, we don't always want. in that case, you can put everything you need in a while that's always true
*/

int main() {  //beginning of code
  vexcodeInit(); // Initializing Robot Configuration. DO NOT REMOVE!


  //task allow_Drive_ForUserTask(allowDriveForUser);

  //task allow_Tray_ForUserTask(allowTrayForUser);

 // task allow_Intake_ForUserTask(allowIntakeForUser);

  task allow_MacroArms_ForUserTask(allowMacroArmsForUser);

 // task allow_ManualArms_ForUserTask(allowManualArmsForUser); 

  while (1){ //always have a while, though if all your functions are tasks (which they should be) then this loop should be empty (note it should still be present)
    task::sleep(20); 
  }
  
}
