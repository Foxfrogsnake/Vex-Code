#include <vector>
using namespace std;
using namespace vex;

class Control{
  vex::motor *FR, *FL, *BR, *BL;
  vex::rotation *R,*L,*B;
  vex::controller *con;
  public:
    Control(vector<vex::motor *> temp, vector<vex::rotation *>en, vex::controller *conTemp){
      FR = temp[0];
      FL = temp[1];
      BR = temp[2];
      BL = temp[3];
      R = en[0];
      L = en[1];
      B = en[2];
      con = conTemp;
    }
    Control(vex::motor *temp){

    }

  void control(){
    vex::controller &conT = *con;
    double R = conT.Axis3.position() - conT.Axis1.position()/1.5;
    double L = conT.Axis3.position() + conT.Axis1.position()/1.5;
    R/=2;
    L/=2;
    vex::motor &FRCur = *FR, &FLCur = *FL;
    FRCur.spin(directionType::fwd, R, velocityUnits::pct);
    FLCur.spin(directionType::fwd, L, velocityUnits::pct);

  }
};
