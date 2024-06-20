#ifndef OLED_MODULE_H
#define OLED_MODULE_H

#include "U8glib.h"

class OLEDModule
{
public:
    OLEDModule();
    void init();
    void showEmptyScreen();
    void displayValues(float temperature, float humidity, int lightLevel, int soundLevel);

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

void OLEDModule::displayValues(float temperature, float humidity, int lightLevel, int soundLevel)
{
    u8g.firstPage();
    do
    {
        u8g.setFont(u8g_font_unifont);

        char buffer[32];
        sprintf(buffer, "Temp: %.2f C", temperature);
        u8g.drawStr(0, 10, buffer);

        sprintf(buffer, "Humidity: %.2f %%", humidity);
        u8g.drawStr(0, 20, buffer);

        sprintf(buffer, "Light: %d %%", lightLevel);
        u8g.drawStr(0, 30, buffer);

        sprintf(buffer, "Sound: %d", soundLevel);
        u8g.drawStr(0, 40, buffer);

    } while (u8g.nextPage());
}
