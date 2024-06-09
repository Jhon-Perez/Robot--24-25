#pragma once
#include "main.h"
#include "globals.hpp"
#include "CyclicIterator.hpp"

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

void setVoltageMotors(int leftMotor, int rightMotor);
void drive();
void incrementJoystick();
