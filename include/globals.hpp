#pragma once
#include "pros/motor_group.hpp"
#include "pros/imu.hpp"

extern pros::MotorGroup leftDriveTrain;
extern pros::MotorGroup rightDriveTrain;

extern pros::MotorGroup intakeMotors;

extern pros::Imu imuSensor;
extern pros::Controller master;
