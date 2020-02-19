using namespace vex;

/*/////INFORMATION/////
THIS IS WHERE YOU DECLARE YOUR ALL ELECTRONIC DEVICES
-use "extern" to tell the program "hey don't worry! there will be a device named "deviceName" somewhere!!!" 
-don't say ports or anything. all you're saying is --> extern device deviceName; 
*/

//brain and controller declarations
extern brain Brain;
extern controller Controller; 

//drive base motor declarations
extern motor rF; 
extern motor rB; 
extern motor lF;
extern motor lB; 

//intake motor declarations
extern motor rin;
extern motor lin;

//arm motor declaration
extern motor arm;

//tilter motor declartion
extern motor tray;   

//limit switch declaration
extern limit trayLimit;


/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void);
