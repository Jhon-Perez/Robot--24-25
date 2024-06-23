#include "autonomous.hpp"
#include "globals.hpp"
#include "pid.hpp"

CyclicIterator page = CyclicIterator(0, 4);

void select() {
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

void runAutonomous() {
    switch (*page) {
		case 0:
			leftAWP();
			break;

		case 1:
			rightAWP();
			break;

		case 2:
			skills();
			break;

		default:
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
