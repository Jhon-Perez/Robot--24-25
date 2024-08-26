#include <cmath>

#include "chassis.hpp"
#include "globals.hpp"
#include "cyclic_iterator.hpp"

const double ANALOG_TO_VOLTAGE = 12000.0 / 127.0;

CyclicIterator joystickIterator(JoystickType::Tank, true);
CyclicIterator polynomialIterator(PolynomialDegree::SEXTIC, true);

const std::string joystickNames[] = {
    "Arcade Left",
    "Arcade Right",
    "Split Arcade",
    "Tank"
};

// void incrementJoystick() {
// 	++joystickIterator;
// }

// void decrementJoystick() {
//     --joystickIterator;
// }

// void incrementPolynomial() {
//     ++polynomialIterator;
// }

// void decrementPolynomial() {
//     --polynomialIterator;
// }

double getAcceleration(int16_t power, uint8_t exponent) {
    if (exponent == 1) {
        return power;
    }

    return pow(power, exponent - 1) / pow(127, exponent - 1) * ((exponent % 2 == 0) ? abs(power) : power);
}

void drive() {
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
        ++joystickIterator;
    }

    uint8_t joystickType = *joystickIterator;

    int16_t power = 0;
    int16_t turn = 0;
    double left = 0;
    double right = 0;
    
    switch (joystickType) {
        case JoystickType::ArcadeLeft:
            power = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
            turn = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);
            break;

        case JoystickType::ArcadeRight:
            power = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
            turn = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
            break;

        case JoystickType::SplitArcade:
            power = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
            turn = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
            break;

        case JoystickType::Tank:
            left = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
            right = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
            break;
    }
    
    if (joystickType != JoystickType::Tank) {
        left = getAcceleration(power + turn, *polynomialIterator);
        right = getAcceleration(power - turn, *polynomialIterator);
    }
    
    leftDriveTrain.move_voltage(left * ANALOG_TO_VOLTAGE);
    rightDriveTrain.move_voltage(right * ANALOG_TO_VOLTAGE);
}

void setBrakeMode(pros::MotorBrake mode) {
    leftDriveTrain.set_brake_mode_all(mode);
    rightDriveTrain.set_brake_mode_all(mode);
}

void switchBrakeMode() {
    if (leftDriveTrain.get_brake_mode() == pros::MotorBrake::coast) {
        setBrakeMode(pros::MotorBrake::brake);
    } else {
        setBrakeMode(pros::MotorBrake::coast);
    }
}
