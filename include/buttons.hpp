#pragma once
#include "main.h"

using lcd_btn = pros::lcd::lcd_btn_cb_fn_t;

class Button {
private:
    lcd_btn left;
    lcd_btn middle;
    lcd_btn right;

public:
    Button(lcd_btn left, lcd_btn middle) : left(left), middle(middle), right(right) {}
    void update();
    
};
