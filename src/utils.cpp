#include "utils.hpp"

// Set the minimum value the motor can be set to
int32_t clamp(int32_t val, int32_t min, int32_t max) {
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