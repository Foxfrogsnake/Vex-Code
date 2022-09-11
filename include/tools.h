#include "math.h"
#include <vector>
using namespace std;
using namespace vex;

vector<double> convertPolar(double x, double y)
{
  double r = sqrt(x*x + y*y);
  double ang = tan(y/x);
  return {ang, r};
}

vector<double> convertCartesian(double r, double ang){
  return {cos(ang) * r, sin(ang) * r};
}

