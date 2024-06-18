#ifndef TH02_MODULE_H
#define TH02_MODULE_H

#include <TH02_dev.h>

class TH02Module
{
public:
    void init();
    float getTemperature();
    float getHumidity();
};

void TH02Module::init()
{
    delay(150); // Wait for voltage to stabilize
    TH02.begin();
    delay(100);
}

float TH02Module::getTemperature()
{
    return TH02.ReadTemperature();
}

float TH02Module::getHumidity()
{
    return TH02.ReadHumidity();
}

#endif
