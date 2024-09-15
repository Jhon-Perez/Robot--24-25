#include "button.hpp"
#include "screen.hpp"

void Button::draw() {
    pros::screen::set_pen(pros::Color::gray);
    pros::screen::fill_rect(x0, y0, x1, y1);

    pros::screen::set_eraser(pros::Color::gray);
    pros::screen::set_pen(pros::Color::black);
    text.print();
}

bool Button::is_pressed(pros::screen_touch_status_s_t* status) const {
    return status->touch_status == 1 &&
           status->x >= x0 && status->x <= x1 &&
           status->y >= y0 && status->y <= y1;
}    

void Button::press(pros::screen_touch_status_s_t* status) {
    bool pressed = is_pressed(status);
    if (pressed && !held) {
        // Some buttons don't have any visual changes
        // making refreshing the screen unnecessary
        if (refresh) {
            pros::screen::erase();
            callback();
            displayScreen();
        } else {
            callback();
        }
    }
}

void Button::editText(std::string text) {
    this->text = Text(x0, y0, x1, y1, text);
}
