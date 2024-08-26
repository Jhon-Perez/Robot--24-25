#include <sstream>

#include "text.hpp"
#include "pros/screen.hpp"

const uint8_t letterWidth = 10;
const uint8_t letterHeight = 15;

Text::Text(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, std::string text) {
    uint16_t x = x0 + (x1 - x0) / 2;
    this->y = y0 + (y1 - y0) / 2;

    std::istringstream stream(text);
    std::vector<std::string> result;
    std::string word;

    while (stream >> word) {
        this->text.push_back(word);
        this->xValues.push_back(x - word.size() * letterWidth / 2);
    }

    this->y -= this->text.size() * letterHeight / 2;
}

void Text::print() {
    for (uint8_t i = 0; i < text.size(); i++) {
        pros::screen::print(pros::E_TEXT_MEDIUM, xValues[i], y + i * letterHeight, "%s", text[i]);
    }
}
