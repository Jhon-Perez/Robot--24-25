#include "intake.hpp"
#include "globals.hpp"

void intake() {
    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
        intakeMotors.move_voltage(12000);
    } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
        intakeMotors.move_voltage(-12000);
    } else {
        intakeMotors.move_voltage(0);
    }
}
