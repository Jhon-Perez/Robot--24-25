/*
 * API for creating buttons on the screen
 *
 * The Page class is a container for buttons. This 
 * part of the API allows for users to easily create
 * pages and easily switch between them as shown in
 * screen.cpp. 
 *
 * Project came to an end so the display is not finished.
 * Functionality works perfectly nonetheless. If you want
 * to go back and finish the display, feel free to do so.
 * 
 * See draw() in button.cpp to continue finishing the display.
 **/

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
