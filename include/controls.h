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
      BR = temp[3];
      BL = temp[4];
      R = en[0];
      L = en[1];
      B = en[2];
      con = conTemp;
    }
    Control(vex::motor *temp){

    }

  void control(){
    vex::controller &conT = *con;
    double R = conT.Axis3.position()/2 - conT.Axis1.position();
    double L = conT.Axis3.position()/2 + conT.Axis1.position();
    R/=2;
    L/=2;
    vex::motor &FRCur = *FR, &FLCur = *FL, &BRCur = *BR, &BLCur = *BL;
    FRCur.spin(directionType::fwd, R, velocityUnits::pct);
    FLCur.spin(directionType::fwd, L, velocityUnits::pct);
    BRCur.spin(directionType::fwd, R, velocityUnits::pct);
    BLCur.spin(directionType::fwd, L, velocityUnits::pct);
  }
};
