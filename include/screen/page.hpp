#pragma once
#include "button.hpp"

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
    Page(std::vector<Button> buttons, function background = []() {}, function design = []() {});

    void draw();
    void interact(pros::screen_touch_status_s_t* status);

private:
    std::vector<Button> buttons;
    const function background;
    const function design;
};
