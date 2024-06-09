#include "buttons.hpp"

void Button::update() {
    uint8_t buttons = pros::lcd::read_buttons();

    if (buttons & LCD_BTN_LEFT) {
        left();
    } 
    
    if (buttons & LCD_BTN_CENTER) {
        middle();
    } 
    
    if (buttons & LCD_BTN_RIGHT) {
        right();
    }
}


