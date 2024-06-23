#pragma once
#include "main.h"

using function = void(*)();

// const int SCREEN_WIDTH = 480;
// const int SCREEN_HEIGHT = 240;

class Button {
public:
    static inline bool held;

    Button(int x0, int y0, int x1, int y1, pros::Color color, const char* text, function callback, bool refresh = true);

    void draw();
    void press(pros::screen_touch_status_s_t* status);
   
private:
    const int x0;
    const int y0;
    const int x1;
    const int y1;
    const pros::Color color;
    const char* text;
    const function callback;
    const bool refresh;
    bool is_pressed(pros::screen_touch_status_s_t* status) const;
    bool was_pressed;
};
