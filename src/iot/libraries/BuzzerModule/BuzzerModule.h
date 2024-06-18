#ifndef BUZZER_MODULE_H
#define BUZZER_MODULE_H

#include "Arduino.h"

class BuzzerModule
{
public:
    BuzzerModule(int pin);
    void init();
    void beep(int frequency, int duration);

private:
    int pin;
};

#endif

BuzzerModule::BuzzerModule(int pin) : pin(pin)
{
}

void BuzzerModule::init()
{
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
}

void BuzzerModule::beep(int frequency, int duration)
{
    tone(pin, frequency, duration);
}