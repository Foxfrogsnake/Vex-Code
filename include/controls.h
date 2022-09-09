#include <vector>
using namespace std;
using namespace vex;

class Control{
  vex::motor *FR, *FL;
  vex::rotation *R,*L,*B;
  vex::controller *con;
  public:
    Control(vector<vex::motor *> temp, vector<vex::rotation *>en, vex::controller *conTemp){
      FR = temp[0];
      FL = temp[1];
      R = en[0];
      L = en[1];
      B = en[2];
      con = conTemp;
    }
    Control(vex::motor *temp){

    }

  void control(){
    vex::controller &conT = *con;
    double R = conT.Axis1.position()/2 - conT.Axis2.position();
    double L = conT.Axis1.position()/2 + conT.Axis2.position();
    R/=2;
    L/=2;
    vex::motor &FRCur = *FR, &FLCur = *FL;
    FRCur.spin(directionType::fwd, R, velocityUnits::pct);
    FLCur.spin(directionType::fwd, L, velocityUnits::pct);
  }
};
