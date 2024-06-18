#ifndef BUTTON_MODULE_H
#define BUTTON_MODULE_H

#include "Arduino.h"

class ButtonModule
{
public:
    ButtonModule(int pin);
    void init();
    void update();
    bool isPressed();

private:
    int pin;
    int state;
};

ButtonModule::ButtonModule(int pin) : pin(pin), state(HIGH)
{
}

void ButtonModule::init()
{
    pinMode(pin, INPUT);
}

void ButtonModule::update()
{
    state = digitalRead(pin);
}

bool ButtonModule::isPressed()
{
    return state == LOW;
}

#endif
