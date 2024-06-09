#pragma once
#include "main.h"

using instruction = void (*)();

class Button {
private:
    instruction left;
    instruction middle;
    instruction right;

public:
    Button(instruction left, instruction middle) : left(left), middle(middle), right(right) {}
    void update();
    
};
