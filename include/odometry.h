#include "vex.h"
#include <vector>
#include "tools.h"

using namespace std;
using namespace vex;

class Odometry{
  //constructor
  public:
    double sR, sL, sB, curO = 0, globalO = 0, prevO = 0;
    double enPrev[3] = {0,0,0}, abPos[2] = {0,0};
    vex::rotation *r,*l,*b;
    vex::controller *control;
    bool screenState = true, buttonAState = false;
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
  void reset(){
    vex::controller con = (*control);

    if(con.ButtonY.pressing()){
    for(int i=0;i<2;i++) abPos[i] =0;
    curO = 0;
    }
  }

  void update(){
    vex::rotation en[3] = {*l, *r, *b};
    double deltaL = en[0].position(rotationUnits::rev) - enPrev[0], deltaR = en[1].position(rotationUnits::rev) - enPrev[1],
     deltaS = en[2].position(rotationUnits::rev) - enPrev[2];
     deltaL *= 0.045, deltaR *= 0.045, deltaS *= 0.045;
    double deltaO = (deltaL - deltaR) / (sR + sL);
    double cenRadius = deltaR / deltaO + sR;
    double deltaY = 0, deltaX = 0;
    curO = deltaO;

    if (deltaO == 0) {
      deltaY = deltaR;
      deltaX = deltaS;
    }
    else if(deltaO != 0){
      deltaY = 2 * sin(deltaO/2) * (deltaR/ deltaO + sR);
      deltaX = 2 * sin(deltaO/2) * (deltaS/ deltaO + sB);
    }
   curO += deltaO;
    // double averageO = globalO + curO/2;
    // vector<double> d1 = convertPolar(deltaX, deltaY);
    // d1[1] += -averageO;
    // d1 = convertCartesian(d1[0], d1[1]);
    // abPos[0] += d1[0];
    // abPos[1] += d1[1];

    abPos[0] += -deltaY * sin(curO) + deltaX * cos(curO);
    abPos[1] += deltaY * cos(curO) + deltaX * sin(curO);

    globalO += curO;

    for(int i=0;i<3;i++){
      enPrev[i] = en[i].position(rotationUnits::rev);
    }
  }

  void graphics() {
    int left_b = 10, right_b = 15, top_b = 6, bottom_b = 11;
      for (int i=top_b; i<bottom_b; i++) {
        for (int j=left_b; j<right_b; j++) {
          if ((i==bottom_b || i==top_b) && (j!=left_b && j!=right_b)) {
            Brain.Screen.setCursor(i,j);
            Brain.Screen.print("_");
          }
          else if ((i!=bottom_b && i!=top_b) && (j==left_b || j==right_b)) {
            Brain.Screen.setCursor(i,j);
            Brain.Screen.print("|");
          }
        }
    }
    Brain.Screen.setCursor(5 + ((int)abPos[0]) % 10,6 + ((int)abPos[1]) % 10);
    Brain.Screen.print("*");
  }
};