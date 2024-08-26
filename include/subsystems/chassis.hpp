#pragma once
#include "pros/motor_group.hpp"
#include "cyclic_iterator.hpp"

enum JoystickType {
    ArcadeLeft,
    ArcadeRight,
    SplitArcade,
    Tank,
};

enum PolynomialDegree {
    LINEAR = 1,
    QUADRATIC = 2,
    CUBIC = 3,
    QUARTIC = 4,
    QUINTIC = 5,
    SEXTIC = 6
};

// lazy way, too tired rn
extern CyclicIterator joystickIterator;
extern CyclicIterator polynomialIterator;

void drive();
void setBrakeMode(pros::MotorBrake mode);
void switchBrakeMode();
void incrementJoystick();
void decrementJoystick();
