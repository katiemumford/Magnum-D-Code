/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       KatieMumford                                              */
/*    Created:      Sun Feb 16 2020                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*/////INFORMATION/////
THIS IS WHERE YOUR MAIN FUNCTION IS
-where you define tasks
*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
using namespace vex;
 


/*task notes

declare and define a task in the main. use this --> vex::task taskName(functionTaskCalls);
the function a task calls must be an int, meaning the function must return an int. which, we don't always want. in that case, you can put everything you need in a while that's always true

*/

int main() {  //beginning of code

// Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  
  task allowDriveForUserTask(allowDriveForUser);
  task allowTrayForUserTask(allowTrayForUser);
  task allowIntakeForUserTask(allowIntakeForUser);
  task allowArmsForUserTask(allowArmsForUser); 

  while (1){ //always have a while, though if all your functions are tasks (which they should be) then this loop should be empty (note it should still be present)
    task::sleep(20); 
  }
  
}
