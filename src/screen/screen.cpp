#include "screen.hpp"
#include "page.hpp"
#include "button.hpp"
#include "autonomous.hpp"

PageType curr = PageType::Menu;
Button home(13, 6, 43, 33, pros::Color::gray, []() { curr = PageType::Menu; });
// Rect back(30, 0, 50, 20, pros::Color::gray, []() {});
// Rect forward(60, 0, 80, 20, pros::Color::gray, []() {});

Page pages[] = {
    // Menu
    Page({
        Button(14,57,127,121, pros::Color::gray, []() { curr = PageType::Autonomous; }),
        Button(162,58,283,120, pros::Color::gray, []() { curr = PageType::DriverControl; }),
        Button(315,58,436,120, pros::Color::gray, []() { curr = PageType::Motors; }),
        Button(15,162,128,221, pros::Color::gray, []() { curr = PageType::TuningPID; }),
        Button(162,162,284,220, pros::Color::gray, []() { curr = PageType::Debug; }),
    }),
    // Autonomous
    Page({
        Button(50,56,117,120, pros::Color::gray, pageUp),
        Button(51,136,115,195, pros::Color::gray, pageDown),
        Button(316,87,424,177, pros::Color::gray, runAutonomous, false),
    }),
    // DriverControl
    Page({
            
    }),
    // might not use a settings page
    Page({

    }),
    // Motors
    Page({

    }),
    // TuningPID
    Page({

    }),
    // Debug
    Page({

    })
};

void displayScreen() {
    pages[curr].draw();
    home.draw();
}

void interactScreen() {
    pros::screen_touch_status_s_t status;
    status = pros::screen::touch_status();
    pages[curr].interact(&status);
    home.press(&status);
    Button::held = status.touch_status == 1;
}
