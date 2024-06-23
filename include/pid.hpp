#pragma once

struct Coordinate {
    double x;
    double y;
};

class PID {
public:
    int calculatePower(double speed);

protected:
    double kP;
    double kI;
    double kD;
    double error;
    int power;
    int timeOut;

    PID(double kP, double kI, double kD, int integralThreshold);
    // int calculatePower(double speed);
    virtual void getError() = 0;
    void powerMotors(int turning);

private:
    double prevError;
    double integral;
    double derivative;

    int integralThreshold;
    int time;
};

class Turn : public PID {
public:
    Turn(double kP, double kI, double kD, int integralThreshold);
    void setTarget(Coordinate target);
    void turnTo(Coordinate target, int timeOut = 5000);
    void turnTo(double target, int timeOut = 5000);

private:
    double target;
    void getError() override;
};

class Drive : public PID {
public:
    Drive(double kP, double kI, double kD, int integralThreshold);
    // void driveTo(Coordinate target, Turn* angular = nullptr, double curvature = 1);
    // void driveTo(Coordinate target, int timeOut = 5000, double speed = 1);
    void driveTo(double target, int timeOut = 5000, double speed = 1);

private:
    Coordinate targetCoords;
    double target;
    double speed;
    void getError() override;
    void setDistance();
};
