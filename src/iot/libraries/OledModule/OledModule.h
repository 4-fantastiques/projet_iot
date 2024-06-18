#ifndef OLED_MODULE_H
#define OLED_MODULE_H

#include "U8glib.h"

class OLEDModule
{
public:
    OLEDModule();
    void init();
    void showEmptyScreen();

private:
    U8GLIB_SSD1306_128X32 u8g;
};

#endif

OLEDModule::OLEDModule() : u8g(U8G_I2C_OPT_NONE)
{
}

void OLEDModule::init()
{
    // Initialization if needed
}

void OLEDModule::showEmptyScreen()
{
    u8g.firstPage();
    do
    {
        // Nothing to draw to show an empty screen
    } while (u8g.nextPage());
}