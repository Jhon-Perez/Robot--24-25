#pragma once

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

void drive();
void incrementJoystick();
void decrementJoystick();
