#include "button.hpp"
#include "screen.hpp"

// Button::Button(int x0, int y0, int x1, int y1, pros::Color color, std::string text, std::function<void()> callback, bool refresh) 
//     : x0(x0), y0(y0), x1(x1), y1(y1), color(color), text(Text(x0, y0, x1, y1, text)), callback(callback), refresh(refresh) {}

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

// Lazy way to change text (creating a new variable)
// instead of changing the text directly (might change)
void Button::editText(std::string text) { // (most likely not because am lazy)
    this->text = Text(x0, y0, x1, y1, text);
}
