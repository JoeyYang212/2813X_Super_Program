#pragma once
#include "lemlib/api.hpp"
#include "pros/misc.h"
#include "pros/misc.hpp"
#include "pros/motors.h"
#include "pros/rtos.hpp"
#include <iostream>

static pros::Controller controller(pros::E_CONTROLLER_MASTER);

static pros::MotorGroup left_motors({-1,-2,-3}, pros::MotorGearset::blue); 
static pros::MotorGroup right_motors({4,5,6}, pros::MotorGearset::blue); 
static lemlib::Drivetrain drivetrain(&left_motors, // left motor group
                              &right_motors, // right motor group
                              11.417, // 10 inch track width
                              lemlib::Omniwheel::NEW_325, // using new 4" omnis
                              450, // drivetrain rpm is 360
                              2 // horizontal drift is 2 (for now)
);

static pros::Imu imu(21);


static pros::Rotation horizontal_encoder(-10);//左右
static pros::Rotation vertical_encoder(9);//前後
// horizontal tracking wheel
static lemlib::TrackingWheel horizontal_tracking_wheel(&horizontal_encoder, lemlib::Omniwheel::NEW_2, 3);
// vertical tracking wheel
static lemlib::TrackingWheel vertical_tracking_wheel(&vertical_encoder, lemlib::Omniwheel::NEW_2, 0);
static lemlib::OdomSensors sensors(nullptr, // vertical tracking wheel 1, set to null
                            nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
                            nullptr, // horizontal tracking wheel 1
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // inertial sensor
);

// lateral PID controller
static lemlib::ControllerSettings lateral_controller(11, // proportional gain (kP)
                                              0.0001, // integral gain (kI)
                                              4, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              2 // maximum acceleration (slew)
);

// angular PID controller
static lemlib::ControllerSettings angular_controller(2.5, // proportional gain (kP)
                                              0.0001, // integral gain (kI)
                                              19, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in degrees
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in degrees
                                              500, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);

// create the chassis
static lemlib::Chassis chassis(drivetrain, // drivetrain settings
                        lateral_controller, // lateral PID settings
                        angular_controller, // angular PID settings
                        sensors // odometry sensors
);
