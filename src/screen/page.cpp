#include "page.hpp"

Page::Page(std::vector<Button> buttons, function background, function design)
    : buttons(buttons), background(background), design(design) {}

void Page::draw() {
    for (auto& button : buttons) {
        button.draw();
    }
    design();
}

void Page::interact(pros::screen_touch_status_s_t* status) {
    for (auto& button : buttons) {
        button.press(status);
    }
}
