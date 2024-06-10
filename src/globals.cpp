#include "globals.hpp"

pros::MotorGroup leftDriveTrain({-15, 17, -9}, pros::MotorGears::rpm_600, pros::MotorEncoderUnits::counts);
pros::MotorGroup rightDriveTrain({14, -16, 8}, pros::MotorGears::rpm_600, pros::MotorEncoderUnits::counts);

pros::MotorGroup intakeMotors({-1, 2}, pros::MotorGears::rpm_600);

pros::Imu imuSensor(5);
pros::Controller master(pros::E_CONTROLLER_MASTER);
