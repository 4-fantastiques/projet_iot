#ifndef LIGHT_SENSOR_MODULE_H
#define LIGHT_SENSOR_MODULE_H

#include "Arduino.h"

class LightSensorModule
{
public:
    LightSensorModule(int pin);
    void init();
    int getLightLevel();

private:
    int pin;
};

LightSensorModule::LightSensorModule(int pin) : pin(pin)
{
}

void LightSensorModule::init()
{
    pinMode(pin, INPUT);
}

int LightSensorModule::getLightLevel()
{
    int rawLightValue = analogRead(pin);
    return map(rawLightValue, 0, 1023, 0, 100);
}

#endif
