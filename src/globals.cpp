#include "globals.hpp"

// Drive Train Motors
// pros::Motor topLeft(-15, pros::MotorGears::rpm_600, pros::MotorEncoderUnits::degrees);
// pros::Motor middleLeft(17, pros::MotorGears::rpm_600, pros::MotorEncoderUnits::degrees);
// pros::Motor bottomLeft(-9, pros::MotorGears::rpm_600, pros::MotorEncoderUnits::degrees);

// pros::Motor topRight(14, pros::MotorGears::rpm_600, pros::MotorEncoderUnits::degrees);
// pros::Motor middleRight(-16, pros::MotorGears::rpm_600, pros::MotorEncoderUnits::degrees);
// pros::Motor bottomRight(8, pros::MotorGears::rpm_600, pros::MotorEncoderUnits::degrees);

pros::MotorGroup leftDriveTrain({-15, 17, -9}, pros::MotorGears::rpm_600, pros::MotorEncoderUnits::counts);
pros::MotorGroup rightDriveTrain({14, -16, 8}, pros::MotorGears::rpm_600, pros::MotorEncoderUnits::counts);

pros::Imu imuSensor(5);
pros::Controller master(pros::E_CONTROLLER_MASTER);
