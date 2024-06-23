#include "main.h"
#include "pid.hpp"
#include "globals.hpp"

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

// Function to log data to a file
void logData(FILE* logFile, double time, double error, double kP, double kI, double kD) {
    // Define a buffer to hold the formatted string
    char buffer[256];
    
    // Format the string using snprintf
    int len = snprintf(buffer, sizeof(buffer), "%.2f,%.2f,%.2f,%.2f,%.2f\n",
                       time, error, error * kP, error * kI, error * kD);

    // Check if snprintf succeeded
    if (len < 0 || len >= sizeof(buffer)) {
        // Handle the error appropriately
        fprintf(stderr, "Error formatting the log string.\n");
        return;
    }
    
    // Write the formatted string to the log file
    fputs(buffer, logFile);
}

PID::PID(double kP, double kI, double kD, int integralThreshold)
    : kP(kP), kI(kI), kD(kD), integralThreshold(integralThreshold) {}

int PID::calculatePower(double speed) {
    getError();
    // Logging Data
    
    derivative = error - prevError;
    integral += error;
    prevError = error;

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
    FILE* usdFile = fopen("/usd/example.txt", "w");


    while (true) {
        power = calculatePower(1);

        if (pros::usd::is_installed()) {
            logData(usdFile, time / 1000.0, error, kP, kI, kD);
        }

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

    fclose(usdFile);

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

Drive::Drive(double kP, double kI, double kD, int integralThreshold)
    : PID(kP, kI, kD, integralThreshold) {}

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

Turn::Turn(double kP, double kI, double kD, int integralThreshold)
    : PID(kP, kI, kD, integralThreshold) {}

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
    this->target = normalizeAngle(target);
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
