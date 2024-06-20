#ifndef SOUND_SENSOR_MODULE_H
#define SOUND_SENSOR_MODULE_H

#include "Arduino.h"

class SoundSensorModule
{
public:
    SoundSensorModule(int pin);
    void init();
    int getSoundLevel();

private:
    int pin;
};

SoundSensorModule::SoundSensorModule(int pin) : pin(pin)
{
}

void SoundSensorModule::init()
{
    pinMode(pin, INPUT);
}

int SoundSensorModule::getSoundLevel()
{
    int rawSoundValue = analogRead(pin);

    float voltage = rawSoundValue * (5 / 1024.0); // Convert analog value to voltage

    // Convert voltage to dB
    float dB = 20 * log10(voltage / 0.00631);

    return dB;
}

#endif