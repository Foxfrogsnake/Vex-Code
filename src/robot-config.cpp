#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor FR = motor(PORT2, ratio18_1, true);
motor FL = motor(PORT1, ratio18_1, false);
motor BR = motor(PORT3, ratio18_1, false);
motor BL = motor(PORT4, ratio18_1, false);
rotation R = rotation(PORT20, true);
rotation L = rotation(PORT19, true);
rotation B = rotation(PORT18, false);
controller Controller1 = controller(primary);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}