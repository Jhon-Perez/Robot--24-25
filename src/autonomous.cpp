#include "autonomous.hpp"
#include "globals.hpp"
#include "pros/screen.hpp"
#include "cyclic_iterator.hpp"

CyclicIterator page(4, false);

void displayAWP() {
    pros::screen::print(pros::E_TEXT_MEDIUM, 171, 78, "page: %d", *page);

    switch (*page) {
        case 0:
            pros::screen::print(pros::E_TEXT_MEDIUM, 172, 130, "Left AWP");
            break;
        case 1:
            pros::screen::print(pros::E_TEXT_MEDIUM, 172, 130, "Right AWP");
            break;
        case 2:
            pros::screen::print(pros::E_TEXT_MEDIUM, 172, 130, "Skills");
            break;
        case 3:
            pros::screen::print(pros::E_TEXT_MEDIUM, 172, 130, "Back");
            break;
    }
}

void pageUp() {
    ++page;
}

void pageDown() {
    --page;
}

uint8_t getPage() {
    return *page;
}

LinearPID drive(0, 0, 0, 0);
AngularPID turn(0, 0, 0, 0);

void leftAWP() {

}

void rightAWP() {

}

void skills() {

}

bool isLinear = false;

PID* getPID() {
    isLinear = !isLinear;
    if (isLinear) {
        pros::screen::print(pros::E_TEXT_MEDIUM, 171, 30, "Linear");
        return &drive;
    } else {
        pros::screen::print(pros::E_TEXT_MEDIUM, 171, 30, "Angular");
        return &turn;
    }
}
