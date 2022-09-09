#include "vex.h"
#include <vector>

using namespace std;
using namespace vex;

class Odometry{
  double sR, sL, sB, curO = 0, prevO = 0;
  double enPrev[3] = {0,0,0}, abPos[2] = {0,0};
  vex::rotation* r,*l,*b;
  vex::controller *control;
  bool screenState = true, buttonAState = false;
  //constructor
  public:
    Odometry(vector<vex::rotation*>encoders, vex::controller *controllerTemp, vector<double> store){
      this->sR = store[0];
      this->sL = store[1];
      this->sB = store[2];
      this->r = encoders[0];
      this->l = encoders[1];
      this->b = encoders[2];
      this->control = controllerTemp;
      for(int i=0;i<3;i++){
        (*encoders[i]).resetPosition();
      }
    }

  //read encoder value into the controller
  public:
    void display(){
      vex::controller con = (*control);
      vex::rotation en[3] = {*l, *r, *b};
      con.Screen.clearScreen();
      if(con.ButtonA.pressing()){
        screenState = true;
      }
      if(con.ButtonB.pressing()){
        screenState = false;
      }
      if(!screenState){
        con.Screen.setCursor(1,1);
        con.Screen.print("l angle = %f"
        ,en[0].position(vex::rotationUnits::rev));
        con.Screen.setCursor(2,1);
        con.Screen.print("r angle = %f"
        ,en[1].position(vex::rotationUnits::rev));
        con.Screen.setCursor(3,1);
        con.Screen.print("b angle = %f"
        ,en[2].position(vex::rotationUnits::rev));
      }else{
        con.Screen.setCursor(1,1);
        con.Screen.print("PosX = %f",
        abPos[0]);
        con.Screen.setCursor(2,1);
        con.Screen.print("PosY = %f",
        abPos[1]);
        con.Screen.setCursor(3,1);
        con.Screen.print("curO = %f",
        curO);
      }
    }

  void update(){
    vex::rotation en[3] = {*l, *r, *b};
    double deltaL = en[0].position(rotationUnits::rev) - enPrev[0], deltaR = en[1].position(rotationUnits::rev) - enPrev[1],
     deltaS = en[2].position(rotationUnits::rev) - enPrev[2];
    double deltaO = (deltaL - deltaR) / (sR + sL);
    double cenRadius = deltaR / deltaO + sR;
    double deltaY = 0, deltaX = 0;
    if(deltaO != 0){
      deltaY = 2 * sin(deltaO/2) * (deltaR/ deltaO + sR);
      deltaX = 2 * sin(deltaO/2) * (deltaS/ deltaO + sB);
    }
    abPos[0] += deltaY * sin(curO) + deltaX * cos(curO);
    abPos[1] += deltaY * sin(curO) + deltaX * cos(curO);

    curO += deltaO;

    for(int i=0;i<3;i++){
      enPrev[i] = en[i].position(rotationUnits::rev);
    }
  }
};