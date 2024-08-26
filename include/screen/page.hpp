#pragma once
#include "button.hpp"
#include "pros/screen.h"

enum PageType {
    Menu,
    Autonomous,
    DriverControl,
    Settings,
    Motors,
    TuningPID,
    Debug
};

// Page type, buttons, background, design
class Page {
public:
    Page(std::vector<Button> buttons, std::function<void()> background = []() {});

    void draw();
    void interact(pros::screen_touch_status_s_t* status);

private:
    std::vector<Button> buttons;
    const std::function<void()> background;
};

PageType getCurrentPage();
void switchPage(PageType page);
