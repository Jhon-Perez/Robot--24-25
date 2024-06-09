#include "chassis.hpp"

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

double polynomial(double power, int exponent) {
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
            pros::lcd::set_text(2, "Arcade Left");
            break;
        case JoystickType::ArcadeRight:
            power = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
            turn = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
            pros::lcd::set_text(2, "Arcade Right");
            break;
        case JoystickType::SplitArcade:
            power = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
            turn = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
            pros::lcd::set_text(2, "Split Arcade");
            break;
        case JoystickType::Tank:
            left = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
            right = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
            pros::lcd::set_text(2, "Tank Drive");
            break;
    }
    
    if (joystickType != JoystickType::Tank) {
        left = polynomial(power + turn, speed);
        right = polynomial(power - turn, speed);
    }
    
    leftDriveTrain.move_voltage(left * ANALOG_TO_VOLTAGE);
    rightDriveTrain.move_voltage(right * ANALOG_TO_VOLTAGE);
}
