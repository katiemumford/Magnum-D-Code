#include "vex.h"
using namespace vex;

/*/////INFORMATION/////
THIS IS WHERE YOU INITIALIZE ALL ELECTRONIC DEVICES FIRST DECLARED IN ROBOT-CONFIG.H
-say device name that was 
-note if you have "using namespace vex" you don't have to say vex:: --> you can just say "motor" or whatever device
*/

// A global instance of brain used for printing to the V5 brain screen
brain Brain;

//initialize controller
controller Controller; 

//initialize drive base motors 
motor rF (vex::PORT10, false);   //right front: port 10 --> correct, note motor facing backwards
motor rB (vex::PORT4, false);   //right back: port 4    --> correct, note motor facing backwards
motor lF (vex::PORT3, true);   //left front: 3          --> correct  
motor lB (vex::PORT12, true); //left back: 12           --> correct 

//initialize intake motors 
motor rin (vex::PORT13, true); //correct
motor lin (vex::PORT9, false); //correct

//inititalize arm motor 
motor arm (vex::PORT11, true); 

//initialize tilter motor 
motor tray(vex::PORT14, true); 

//initialize the limit switch
limit trayLimit = limit(Brain.ThreeWirePort.H);


/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void) {
}