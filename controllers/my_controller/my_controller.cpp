// File:          my_controller.cpp
// Date:
// Description:
// Author:
// Modifications:

// You may need to add webots include files such as
// <webots/DistanceSensor.hpp>, <webots/Motor.hpp>, etc.
// and/or to add some other includes
#include <webots/Robot.hpp>
#include <webots/PositionSensor.hpp>
#include <webots/Motor.hpp>
#include <webots/GPS.hpp>

#include <limits>
#include <iostream>
#include <fstream>
// All the webots classes are defined in the "webots" namespace
using namespace webots;

// This is the main program of your controller.
// It creates an instance of your Robot instance, launches its
// function(s) and destroys it at the end of the execution.
// Note that only one instance of Robot should be created in
// a controller program.
// The arguments of the main function can be specified by the
// "controllerArgs" field of the Robot node
namespace Constants
{
constexpr double CarWheelRadius = 0.36;
constexpr double TwoPI = 6.28318530718;
constexpr double DefaultPreviousPosition = -42.0;
constexpr double Millisecond = 0.001; //sec
constexpr double DefaultVelocity = 50.0; // m/s
constexpr double DefaultVehicleSpeed = DefaultVelocity / Constants::CarWheelRadius; // m/s / R
}
int main(int argc, char **argv) {
  // create the Robot instance.
  Robot *robot = new Robot();

  // get the time step of the current world.
  int timeStep = (int)robot->getBasicTimeStep();

  // You should insert a getDevice-like function in order to get the
  // instance of a device of the robot. Something like:
  //  Motor *motor = robot->getMotor("motorname");
  //  DistanceSensor *ds = robot->getDistanceSensor("dsname");
  //  ds->enable(timeStep);

  // Main loop:
  // - perform simulation steps until Webots is stopping the controller
  double leftPreviousPosition = Constants::DefaultPreviousPosition;
  double rightPreviousPosition = Constants::DefaultPreviousPosition;
  std::ofstream myfile;
  myfile.open("SpeedVsGPSTS_" + std::to_string(timeStep) + ".csv");
  myfile << "WheelSpeed,GPSSpeed,CommandedSpeed" << std::endl;
  while (robot->step(timeStep) != -1) {
    // Read the sensors:
    // Enter here functions to read sensor data, like:
    //  double val = ds->getValue();
    
    Motor *leftSteer = robot->getMotor("left_rear_wheel");
    Motor *rightSteer = robot->getMotor("right_rear_wheel");
    PositionSensor *leftPosition = robot->getPositionSensor("left_rear_sensor");
    PositionSensor *rightPosition = robot->getPositionSensor("right_rear_sensor");
    GPS *gps = robot->getGPS("GPS");
    gps->enable(timeStep);


    leftPosition->enable(timeStep);
    rightPosition->enable(timeStep);
    leftSteer->setPosition(std::numeric_limits<double>::infinity());
    rightSteer->setPosition(std::numeric_limits<double>::infinity());

    leftSteer->setVelocity(Constants::DefaultVehicleSpeed);
    rightSteer->setVelocity(Constants::DefaultVehicleSpeed);
    double avgChangeRotationalPosition = 0.0;
    if(leftPreviousPosition != Constants::DefaultPreviousPosition)
    {
      const double currentLeftPosition = leftPosition->getValue();
      const double currentRightPosition = rightPosition->getValue();
      avgChangeRotationalPosition = ((currentLeftPosition - leftPreviousPosition) + (currentRightPosition - rightPreviousPosition)) / 2.0; //rads
      leftPreviousPosition = currentLeftPosition;
      rightPreviousPosition = currentRightPosition;
    }
    else
    {
      leftPreviousPosition = leftPosition->getValue();
      rightPreviousPosition = rightPosition->getValue();
    }
    
    const double avgWheelSpeed = avgChangeRotationalPosition / (timeStep * Constants::Millisecond) * Constants::CarWheelRadius;
    const double gpsSpeed = gps->getSpeed();
    std::cout << "WS: " << avgWheelSpeed << " GS: " << gpsSpeed << std::endl;
    // Write to file for graphing
    myfile << avgWheelSpeed << "," << gpsSpeed << "," << Constants::DefaultVelocity << std::endl;
  };

  // Enter here exit cleanup code.

  delete robot;
  myfile.close();
  return 0;
}
