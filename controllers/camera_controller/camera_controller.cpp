#include <webots/Robot.hpp>
#include <webots/GPS.hpp>
#include <webots/DistanceSensor.hpp>
#include <webots/Motor.hpp>
#include <webots/Keyboard.hpp>
#include <webots/InertialUnit.hpp>
#include <webots/Gyro.hpp>
#include <webots/Accelerometer.hpp>
#include <webots/Compass.hpp>
#include <webots/Camera.hpp>

 
#include <webots/Receiver.hpp>
 

#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <limits>
#include <string>

#define TIME_STEP 64
// All the webots classes are defined in the "webots" namespace
using namespace webots;
using namespace std;
int main(int argc, char **argv) {
  // create the Robot instance.
  Robot *robot = new Robot();
  Keyboard kb;
  kb.enable(TIME_STEP);
  
  DistanceSensor *ds[2];
  char dsNames[2][10] = {"ds_right","ds_left"};
  for (int i = 0; i < 2; i++) {
    ds[i] = robot->getDistanceSensor(dsNames[i]);
    ds[i]->enable(TIME_STEP);
  }
 
  Camera *camera;
  //camera=getCamera("camera");
  camera=robot->getCamera("camera");
  camera->enable(TIME_STEP);
  
  // initialise motors
  Motor *wheels[4];
  char wheels_names[4][8] = {"wheel1", "wheel2", "wheel3", "wheel4"};
  for (int i = 0; i < 4; i++) {
    wheels[i] = robot->getMotor(wheels_names[i]);
    wheels[i]->setPosition(INFINITY);
    wheels[i]->setVelocity(0);
  }
  printf("init successd ...\n");
   
  double leftSpeed = 0.0;
  double rightSpeed = 0.0;

   // Main loop:
  // - perform simulation steps until Webots is stopping the controller
 while (robot->step(TIME_STEP) != -1)
 {
   //const unsigned char *dat= camera->getImage();
    int key = kb.getKey();
    cout<<key<<endl;
    if(key== 73)
    {
      leftSpeed = 3.0;
      rightSpeed = 3.0;
    }
    else if(key== 44)
    {
      leftSpeed = -3.0;
      rightSpeed = -3.0;
    }
    else if(key== 74)
    {
      leftSpeed = -3.0;
      rightSpeed = 3.0;
    }
    else if(key== 76)
    {
      leftSpeed = 3.0;
      rightSpeed = -3.0;
    }
    else  
    {
      leftSpeed = 0.0;
      rightSpeed = 0.0;
    }
    
     wheels[0]->setVelocity(leftSpeed);
     wheels[1]->setVelocity(rightSpeed);
     wheels[2]->setVelocity(leftSpeed);
     wheels[3]->setVelocity(rightSpeed);
  };

  // Enter here exit cleanup code.

  delete robot;
  return 0;
}