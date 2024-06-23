#include "chassis.hpp"
#include "globals.hpp"
#include "cyclic_iterator.hpp"

const double ANALOG_TO_VOLTAGE = 12000.0 / 127.0;
const PolynomialDegree speed = LINEAR;

CyclicIterator joystickIterator(JoystickType::ArcadeLeft, JoystickType::Tank);

const char* const joystickNames[] = {
    "Arcade Left",
    "Arcade Right",
    "Split Arcade",
    "Tank"
};

void incrementJoystick() {
	++joystickIterator;
    pros::lcd::print(2, "Joystick: %s", joystickNames[*joystickIterator]);
}

void decrementJoystick() {
    --joystickIterator;
    pros::lcd::print(2, "Joystick: %s", joystickNames[*joystickIterator]);
}

double getAcceleration(double power, int exponent) {
    if (exponent == 1) {
        return power;
    }

    return pow(power, exponent - 1) / pow(127, exponent - 1) * ((exponent % 2 == 0) ? abs(power) : power);
}

void drive() {
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
        ++joystickIterator;
    }

    int joystickType = *joystickIterator;

    double left = 0;
    double right = 0;
    double power = 0;
    double turn = 0;

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
        left = getAcceleration(power + turn, speed);
        right = getAcceleration(power - turn, speed);
    }
    
    leftDriveTrain.move_voltage(left * ANALOG_TO_VOLTAGE);
    rightDriveTrain.move_voltage(right * ANALOG_TO_VOLTAGE);
}
