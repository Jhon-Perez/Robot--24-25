/*
 * API for creating buttons on the screen
 *
 * Project came to an end so the display is not finished.
 * Functionality works perfectly nonetheless. If you want
 * to go back and finish the display, feel free to do so.
 * 
 * See draw() in button.cpp to continue finishing the display.
 **/

#pragma once
#include "text.hpp"

#include <functional>

#include "pros/colors.hpp"
#include "pros/screen.hpp"

// const int SCREEN_WIDTH = 480;
// const int SCREEN_HEIGHT = 240;

class Button {
public:
    static inline bool held;

    /*
     * callback is a function that takes any number of arguments
     * to add functionality to every button press. See screen.cpp
     * for examples.
     **/
    template <typename Func, typename... Args>
    Button(
        uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, 
        std::string text, 
        bool refresh, 
        Func callback, 
        Args... args
    ) : x0(x0), y0(y0), x1(x1), y1(y1), 
        text(Text(x0, y0, x1, y1, text)), 
        refresh(refresh), 
        callback(std::bind(callback, args...)) 
    {}
    
    template <typename Func, typename... Args>
    Button(
        uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, 
        std::string text, 
        Func callback, 
        Args... args
    ) : Button(x0, y0, x1, y1, text, true, callback, args...) {}

    void draw();
    void press(pros::screen_touch_status_s_t* status);
    void editText(std::string text);
   
private:
    const uint16_t x0;
    const uint16_t y0;
    const uint16_t x1;
    const uint16_t y1;
    const std::function<void()> callback;
    Text text;
    const bool refresh;
    bool is_pressed(pros::screen_touch_status_s_t* status) const;
    bool was_pressed;
};
