#pragma once
#include <string>
#include <cstdint>

struct Coordinate {
    double x;
    double y;
};

enum Constant {
    Proportional,
    Integration,
    Derivative,
    IntegralThreshold
};

class PID {
public:
    void adjustConstant(uint8_t constant, int16_t value);
    std::pair<int32_t, std::string> getConstant(uint8_t constant) const;

protected:
    PID(int32_t kP, int32_t kI, int32_t kD, int32_t integralThreshold);
    virtual double getError() const = 0;
    void run(int8_t turning);

    uint16_t timeOut;

private:
    int32_t kP;
    int32_t kI;
    int32_t kD;
    int32_t integralThreshold;
};

class LinearPID : public PID {
public:
    LinearPID(int32_t kP, int32_t kI, int32_t kD, int32_t integralThreshold);
    // void driveTo(Coordinate target, Turn* angular = nullptr, double curvature = 1);
    // void driveTo(Coordinate target, int timeOut = 5000, double speed = 1);
    void driveTo(double target, uint16_t timeOut = 5000, double speed = 1);

private:
    Coordinate targetCoords;
    double target;
    double speed;
    double getError() const override;
    void setDistance();
};

class AngularPID : public PID {
public:
    AngularPID(int32_t kP, int32_t kI, int32_t kD, int32_t integralThreshold);
    // Anything with globalX, globalY or Coordinate was from last year when I was using Odometry.
    void setTarget(Coordinate target);
    void turnTo(Coordinate target, uint16_t timeOut = 5000);
    void turnTo(double target, uint16_t timeOut = 5000);

private:
    double target;
    double getError() const override;
};
