#include "vex.h"
#include "string.h"
#include <cmath>

typedef struct {
  float sensor;
  float kP = 0.0;
  float kI = 0.0;
  float kD = 0.0;
  float target;
  float err;
	float prev_err;
	float integral;
	float integral_bound;
	float derivative;
} PIDcontroller;

float wheel_radius = 0.3;
float wheel_circumference = 2*3.141592653589793* wheel_radius;

//Create a variable with PIDcontroller structure
void initializePID(PIDcontroller &controller, vex::motor FR, vex::motor FL, float kP, float kI, float kD, float integral_bound) {
  //avg value of front wheels
  controller.sensor = 0.5*(FR.position(vex::rotationUnits::rev) + FL.position(vex::rotationUnits::rev));
  controller.kP = kP;
  controller.kI = kI;
  controller.kD = kD;
  controller.integral = 0;
  controller.derivative = 0;
  controller.integral_bound = integral_bound;
}

//Update PID
int update(PIDcontroller &controller, float target, int delay = 0) {
  controller.prev_err = controller.err;
	controller.err = controller.target - wheel_circumference * controller.sensor;
  //integral
	if(abs(controller.err) < controller.integral_bound) {
		controller.integral += controller.err;
	}
	else {
		controller.integral = 0;
	}
  //derivative
	controller.derivative = controller.err - controller.prev_err;
	//delay
  vex::task::sleep(delay);

	return controller.kP * controller.err + controller.kI * controller.integral + controller.kD * controller.derivative;
}

void pre_auton() {
}

task autonomous()
{
  return 0;
}

task usercontrol()
{
  while (true)
  {
    return 0;
  }
}

void PID(PIDcontroller &controller, float target) {
  bool goal = 0;
  float dist;
  while (goal) {
    dist = update(controller, target, 10);
    FR.spin(fwd, dist, rpm);
    FL.spin(fwd, dist, rpm);
    if (dist < 1) {
      goal = 1;
    }
  }
}
