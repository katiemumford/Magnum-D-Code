#include "vex.h"
using namespace vex;

//all arm related functions

//in a .cpp file, always include the #include "vex.h" as well as using namespace vex;

 int minPct = 5; //minimum controller value (%) for drive, accounts for stick drift

 void setDrive(double l, double r) { //voltage drive
  if (l < minPct && l > -minPct) { l = 0; }
  if (r < minPct && r > -minPct) { r = 0; } //accounts for stick drift
  l *= 12.0/100;
  r *= 12.0/100; //converts to volts

  lF.spin(vex::directionType::fwd, l, vex::voltageUnits::volt);
  lB.spin(vex::directionType::fwd, l, vex::voltageUnits::volt);
  rF.spin(vex::directionType::fwd, r, vex::voltageUnits::volt);
  rB.spin(vex::directionType::fwd, r, vex::voltageUnits::volt);
}

int allowDriveForUser(){     //function that task calls
  while (true){
    setDrive(Controller.Axis3.value()*100/127.0, Controller.Axis2.value()*100/127.0);
    task::sleep(5);
  }
  return 1;
}