#include <cmath>
#include <fstream>

#include "pid.hpp"
#include "globals.hpp"
#include "utils.hpp"

#define MOTOR_INDEX 1

// 36:1 1800
// 18:1 900
// 6:1 300
const uint16_t ticksPerRevolution = 
    rightDriveTrain.get_gearing() == pros::MotorGears::ratio_36_to_1 ? 1800 :
    rightDriveTrain.get_gearing() == pros::MotorGears::ratio_18_to_1 ? 900 : 300;

// Change ticks per revolution to 360 if encoder units are degrees
// 2 * radius * PI / gear ratio / ticks per revolution
const double distancePerTick = 2 * 2 * M_PI / 1.75 / ticksPerRevolution;
PID::PID(int32_t kP, int32_t kI, int32_t kD, int32_t integralThreshold)
    : kP(kP), kI(kI), kD(kD), integralThreshold(integralThreshold) {}

void PID::run(int8_t turning) {
    double error = 0;
    double prevError = 0;
    double integral = 0;
    double derivative = 0;

    int32_t power = 0;
    uint16_t time = 0;

    std::ofstream usdFile("/usd/example.csv");

    while (true) {
        error = getError();
        derivative = error - prevError;
        prevError = error;

        if (fabs(error) < integralThreshold) {
            integral += error;
        } else {
            integral = 0;
        }

        if (pros::usd::is_installed()) {
            usdFile << time << ','
                    << error << ','
                    << kP << ','
                    << kI << ','
                    << kD << '\n';
        }

        if (fabs(error) < 1 || time > timeOut) {
            break;
        }

        power = error * kP + integral * kI + derivative * kD;

        leftDriveTrain.move_voltage(power);
        rightDriveTrain.move_voltage(power * turning);

        pros::delay(10);
        time += 10;
    }

    leftDriveTrain.move_voltage(0);
    rightDriveTrain.move_voltage(0);

    usdFile.close();

    pros::delay(250);
}

// Wanted to experiment with custom PID tuning and displaying all the values easily.
// Don't think this was the best implementation, feel free to find another solution.
void PID::adjustConstant(uint8_t constant, int16_t value) {
    switch (constant) {
        case Constant::Proportional:
            kP += value;
            break;

        case Constant::Integration:
            kI += value;
            break;

        case Constant::Derivative:
            kD += value;
            break;

        case Constant::IntegralThreshold:
            integralThreshold += value;
            break;
    }
}

// Wanted to experiment with custom PID tuning and displaying all the values easily.
// Don't think this was the best implementation, feel free to find another solution.
std::pair<int32_t, std::string> PID::getConstant(uint8_t constant) const {
    switch (constant) {
        case Constant::Proportional:
            return {kP, "kP"};

        case Constant::Integration:
            return {kI, "kI"};

        case Constant::Derivative:
            return {kD, "kD"};

        default:
            return {integralThreshold, "iT"};
    }
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

LinearPID::LinearPID(int32_t kP, int32_t kI, int32_t kD, int32_t integralThreshold)
    : PID(kP, kI, kD, integralThreshold) {}

void LinearPID::driveTo(double target, uint16_t timeOut, double speed) {
    this->target = target;
    this->timeOut = timeOut;
    this->speed = speed;

    rightDriveTrain.tare_position(MOTOR_INDEX);
    run(1);
}

// Placeholders so I can compile the code. 
// Anything with globalX, globalY or Coordinate was from last year when I was using Odometry.
int globalX;
int globalY;

void LinearPID::setDistance() {
    this->target = sqrt(pow(targetCoords.x - globalX, 2) + pow(targetCoords.y - globalY, 2));
    
    rightDriveTrain.tare_position(MOTOR_INDEX);
    run(1);
}

double LinearPID::getError() const {
    return target - rightDriveTrain.get_position(MOTOR_INDEX) * distancePerTick;
}

AngularPID::AngularPID(int32_t kP, int32_t kI, int32_t kD, int32_t integralThreshold)
    : PID(kP, kI, kD, integralThreshold) {}

void AngularPID::setTarget(Coordinate target) {
    this->target = atan2(target.y - globalY, target.x - globalX);
    // this->target = normalizeAngle(angle - imuSensor.get_yaw());
}

void AngularPID::turnTo(Coordinate target, uint16_t timeOut) {
    setTarget(target);
    this->timeOut = timeOut;

    run(-1);
}

void AngularPID::turnTo(double target, uint16_t timeOut) {
    this->target = normalizeAngle(target);
    this->timeOut = timeOut;

    run(-1);
}

double AngularPID::getError() const {
    return normalizeAngle(target - imuSensor.get_yaw());
}
