#include "buttons.hpp"

void Button::update() {
    uint8_t buttons = pros::lcd::read_buttons();

    if ((buttons & LCD_BTN_LEFT) >> 2) {
        left();
    } 
    
    if ((buttons & LCD_BTN_CENTER) >> 1) {
        middle();
    } 
    
    if ((buttons & LCD_BTN_RIGHT) >> 0) {
        right();
    }
}
