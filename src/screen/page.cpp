#include "page.hpp"

Page::Page(std::vector<Button> buttons, std::function<void()> background)
    : buttons(buttons), background(background) {}

void Page::draw() {
    for (auto& button : buttons) {
        button.draw();
    }
    background();
}

void Page::interact(pros::screen_touch_status_s_t* status) {
    for (auto& button : buttons) {
        button.press(status);
    }
}

PageType currentPage = PageType::Menu;

PageType getCurrentPage() {
    return currentPage;
}

void switchPage(PageType page) {
    currentPage = page;
}
