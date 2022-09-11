// To complete the VEXcode Pro V5 project upgrade process, please follow the
// steps below.
// 
// 1. You can use the Robot Configuration window to recreate your V5 devices
//   - including any motors, sensors, 3-wire devices, and controllers.
// 
// 2. All previous code located in main.cpp has now been commented out. You
//   will need to migrate this code to the new "int main" structure created
//   below and keep in mind any new device names you may have set from the
//   Robot Configuration window. 
// 
// If you would like to go back to your original project, a complete backup
// of your original (pre-upgraded) project was created in a backup folder
// inside of this project's folder.

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// FR                   motor         2               
// FL                   motor         1               
// R                    rotation      20              
// L                    rotation      19              
// B                    rotation      18              
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "controls.h"
#include "odometry.h"
#include "tools.h"
#include "pid.h"
using namespace vex;

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  double sR = 0, sL = 0, sB = 0;
  Control con({&FR, &FL, &BR, &BL}, {&R, &L, &B}, &Controller1);
  Odometry odo({&R, &L, &B}, &Controller1, {sR, sL, sB});
  PIDcontroller wheelPID;
  initializePID(wheelPID, FR, FL, 0, 0, 0, 0);
  while(true){
    con.control();
    odo.display();
    PID(wheelPID, 0);
  }
}

// /*----------------------------------------------------------------------------*/
// /*                                                                            */
// /*    Module:       main.cpp                                                  */
// /*    Author:       19480                                                     */
// /*    Created:      Wed Apr 20 2022                                           */
// /*    Description:  V5 project                                                */
// /*                                                                            */
// /*----------------------------------------------------------------------------*/
// 
// // ---- START VEXCODE CONFIGURED DEVICES ----
// // Robot Configuration:
// // [Name]               [Type]        [Port(s)]
// 