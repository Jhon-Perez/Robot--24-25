#include "main.h"
#include "pid.hpp"
#include "globals.hpp"
#include <fstream>

#define MOTOR_INDEX 1

const int diameter = 4;
const double gearRatio = 1.75;
const double distancePerDegree = diameter * M_PI / gearRatio / 360;

// Set the minimum value the motor can be set to
int clamp(int val, int min, int max) {
    if (val < min) {
        val = min;
    } 
    if (val > max) {
        val = max;
    }
    return val;
}

// Normalize the angle to the range [-180, 180]
double normalizeAngle(double angle) {
    if (angle > 180) {
        angle -= 360;
    } else if (angle < -180) {
        angle += 360;
    }
    return angle;
}

PID::PID(double kP, double kI, double kD, int integralThreshold) {
    this->kP = kP;
    this->kI = kI;
    this->kD = kD;
    this->integralThreshold = integralThreshold;
}

int PID::calculatePower(double speed, int time, FILE* logFile, bool logData) {
    getError();
    // Logging Data
    
    derivative = error - prevError;
    integral += error;
    prevError = error;

    if (pros::usd::is_installed()) {
        fputs((std::to_string(time) + "," + std::to_string(error) + "," + std::to_string(error * kP) + "," + std::to_string(error * kI) + ","  + std::to_string(error * kD) +  "\n").c_str(), logFile);
    }

    if (fabs(error) < integralThreshold) {
        integral += error;
    } else {
        integral = 0;
    }

    power = error * kP + integral * kI + derivative * kD;
    
    return clamp(power * speed, -12000, 12000);
}

void PID::powerMotors(int turning) {
    int time = 0;
    FILE* usd_file_write = fopen("/usd/example.txt", "w");


    while (true) {
        power = calculatePower(1, time, usd_file_write, false);

        if (fabs(error) < 1 || time > timeOut) {
            break;
        }

        leftDriveTrain.move_voltage(power);
        rightDriveTrain.move_voltage(power * turning);

        pros::delay(10);
        time += 10;
    }

    leftDriveTrain.move_voltage(0);
    rightDriveTrain.move_voltage(0);

    fclose(usd_file_write);

    pros::delay(250);
}

// void Drive::driveTo(Coordinate target, int timeOut, double speed) {
//     this->target = sqrt(pow(target.x - globalX, 2) + pow(target.y - globalY, 2));
//     this->timeOut = timeOut;
//     this->speed = speed;

//     pros::lcd::print(7, "x: %f y: %f", target.x - globalX, target.y - globalY);
//     pros::lcd::print(6, "triball 1: %f", this->target);
    
//     bottomRight.tare_position();
//     powerMotors(1);
// }

void Drive::driveTo(double target, int timeOut, double speed) {
    this->target = target;
    this->timeOut = timeOut;
    this->speed = speed;

    rightDriveTrain.tare_position(MOTOR_INDEX);
    powerMotors(1);
}

// Placeholders so I can compile the code
int globalX;
int globalY;

void Drive::setDistance() {
    this->target = sqrt(pow(targetCoords.x - globalX, 2) + pow(targetCoords.y - globalY, 2));
    
    rightDriveTrain.tare_position(MOTOR_INDEX);
    powerMotors(1);
}

void Drive::getError() {
    this->error = target - rightDriveTrain.get_position(MOTOR_INDEX) * distancePerDegree;
}

void Turn::setTarget(Coordinate target) {
    this->target = atan2(target.y - globalY, target.x - globalX);
    pros::lcd::print(6, "target: %f", target);
    // this->target = normalizeAngle(angle - imuSensor.get_yaw());
}

void Turn::turnTo(Coordinate target, int timeOut) {
    setTarget(target);
    this->timeOut = timeOut;

    powerMotors(-1);
}

void Turn::turnTo(double target, int timeOut) {
    this->target = target;
    this->timeOut = timeOut;

    getError();
    if (fabs(error) > 10) {
        this->kP = 0.55 * 1000;
        this->kI = 0 * 1000;
        this->kD = 5.5 * 1000;
    } else {
      this->kP = 0.55 * 1000;
      this->kI = 0.05 * 1000;
      this->kD = 5.5 * 1000;  
    }

    powerMotors(-1);
}

void Turn::getError() {
    this->error = normalizeAngle(target - imuSensor.get_yaw());
}
