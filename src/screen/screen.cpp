/*
 * screen.cpp is full of examples of how to use the API and how
 * I utilized it to create a screen for the robot with features
 * such as an autonomous selector, driver control settings for
 * switching to different control schemes, and PID tuning to
 * quickly tune PID without having to wait long amounts of time
 * when recompiling project.
 */

#include "main.h"
#include "screen.hpp"
#include "page.hpp"
#include "button.hpp"
#include "autonomous.hpp"
#include "cyclic_iterator.hpp"
#include "subsystems/chassis.hpp"

Button home(0, 0, 40, 40, "Home", switchPage, PageType::Menu);

PID* pid = getPID();

CyclicIterator pidConstants(Constant::IntegralThreshold, true);

void tuningBackground() {
    std::pair<int32_t, std::string> constantPair = pid->getConstant(*pidConstants);

    pros::screen::print(pros::E_TEXT_LARGE, 234, 124, "%05d%s", constantPair.first, constantPair.second);
}

Page pages[] = {
    Page({
        Button(14,57,127,121, "Auton Selection", switchPage, PageType::Autonomous),
        Button(162,58,283,120, "Driver Control", switchPage, PageType::DriverControl),
        Button(315,58,436,120, "Motors Info", switchPage, PageType::Motors),
        Button(15,162,128,221, "PID Tuning", switchPage, PageType::TuningPID),
        Button(162,162,284,220, "Debugging", switchPage, PageType::Debug),
    }),
    // Autonomous
    Page({
        Button(50,56,117,120, "Next", pageUp),
        Button(51,136,115,195, "Back", pageDown),
        Button(316,87,424,177, "Test", false, autonomous),
    }, displayAWP),
    // Driver Control
    Page({
        Button(80,49,131,94, "Back", &CyclicIterator::operator--, &polynomialIterator),
        Button(326,48,382,95, "Next", &CyclicIterator::operator++, &polynomialIterator),
        Button(80,112,131,159, "Back", &CyclicIterator::operator--, &joystickIterator),
        Button(329,113,384,163, "Next", &CyclicIterator::operator++, &joystickIterator),
        Button(80,177,131,224, "Brake", []() {}), // I don't think I can change the text
    }),
    // might not use a settings page
    Page({

    }),
    // Motors
    Page({

    }),
    // Tuning PID
    Page({
        Button(44,74,126,116, "Test", false, []() {
            if (auto linearPid = dynamic_cast<LinearPID*>(pid)) {
                linearPid->driveTo(100.0);
            } else if (auto angularPid = dynamic_cast<AngularPID*>(pid)) {
                angularPid->turnTo(45.0);
            }
        }),
        Button(47,148,125,185, "Switch", getPID),
        Button(168,119,211,148, "Back", &CyclicIterator::operator--, &pidConstants),
        Button(402,120,446,147, "Next", &CyclicIterator::operator++, &pidConstants),
        Button(238,80,257,109, "+", &PID::adjustConstant, pid, *pidConstants, 10000),
        Button(238,159,258,187, "-", &PID::adjustConstant, pid, *pidConstants, -10000),
        Button(271,81,293,109, "+", &PID::adjustConstant, pid, *pidConstants, 1000),
        Button(272,159,294,187, "-", &PID::adjustConstant, pid, *pidConstants, -1000),
        Button(308,80,330,110, "+", &PID::adjustConstant, pid, *pidConstants, 100),
        Button(309,162,333,189, "-", &PID::adjustConstant, pid, *pidConstants, -100),
        Button(352,79,375,112, "+", &PID::adjustConstant, pid, *pidConstants, 10),
        Button(354,160,378,192, "-", &PID::adjustConstant, pid, *pidConstants, -10),
    }, tuningBackground),
    // Debug
    Page({
        // This page will contain print statements when I need to debug
    })
};

void displayScreen() {
    pages[getCurrentPage()].draw();
    home.draw();
}

void interactScreen() {
    pros::screen_touch_status_s status;
    status = pros::screen::touch_status();
    pages[getCurrentPage()].interact(&status);
    home.press(&status);
    Button::held = status.touch_status == 1;
}
