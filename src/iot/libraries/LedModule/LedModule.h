#ifndef LED_MODULE_H
#define LED_MODULE_H

#include "Arduino.h"

class LEDModule
{
public:
    LEDModule(int pin);
    void init();
    void turnOn();
    void turnOff();

private:
    int pin;
};

#endif

LEDModule::LEDModule(int pin) : pin(pin)
{
}

void LEDModule::init()
{
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
}

void LEDModule::turnOn()
{
    digitalWrite(pin, HIGH);
}

void LEDModule::turnOff()
{
    digitalWrite(pin, LOW);
}