#include "autonomous.hpp"

CyclicIterator page = CyclicIterator(0, 4);

void select() {
    pros::lcd::print(0, "Page: %d", *page + 1);

    switch (*page) {
        case 0:
            pros::lcd::print(1, "Left AWP");
            break;
        case 1:
            pros::lcd::print(1, "Right AWP");
            break;
        case 2:
            pros::lcd::print(1, "Skills");
            break;
        case 3:
            pros::lcd::print(1, "No Auton");
            break;
    }
}

void pageUp() {
    ++page;
    select();
}

void pageDown() {
    --page;
    select();
}

void leftAWP() {

}

void rightAWP() {

}

void skills() {

}
