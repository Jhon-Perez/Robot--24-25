#pragma once
#include <string>
#include <vector>
#include <cstdint>

class Text {
public:
    Text(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, std::string text);

    void print();

private:
    uint16_t y;
    std::vector<uint16_t> xValues;
    std::vector<std::string> text;
};
