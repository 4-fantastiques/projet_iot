#include "libraries/ButtonModule/ButtonModule.h"
#include "libraries/LightSensor/LightSensor.h"
#include "libraries/TH02Module/TH02Module.h"
#include "Arduino.h"
#include <SoftwareSerial.h>

#define buttonRedPin 5
#define buttonGreenPin 4
#define LIGHT_SENSOR_PIN A3
#define SERIAL_BAUD_RATE 9600
#define RX_PIN 10
#define TX_PIN 11

ButtonModule buttonRed(buttonRedPin);
ButtonModule buttonGreen(buttonGreenPin);
LightSensorModule lightSensor(LIGHT_SENSOR_PIN);
TH02Module th02Sensor;

SoftwareSerial mySerial(RX_PIN, TX_PIN); // RX, TX

void setup()
{
    Serial.begin(SERIAL_BAUD_RATE);   // Start serial communication
    mySerial.begin(SERIAL_BAUD_RATE); // Start software serial communication
    buttonRed.init();
    buttonGreen.init();
    lightSensor.init();
    th02Sensor.init();

    Serial.println("TH02_dev is available.\n");
}

void loop()
{
    buttonRed.update();
    buttonGreen.update();

    if (buttonRed.isPressed())
    {
        Serial.println("Button Red is pressed");
    }
    else
    {
        Serial.println("Button Red is not pressed");
    }

    if (buttonGreen.isPressed())
    {
        Serial.println("Button Green is pressed");
    }
    else
    {
        Serial.println("Button Green is not pressed");
    }

    int lightLevel = lightSensor.getLightLevel();
    float temperature = th02Sensor.getTemperature();
    float humidity = th02Sensor.getHumidity();

    // Print to serial monitor
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println("C");

    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println("%");

    Serial.print("Light level: ");
    Serial.print(lightLevel);
    Serial.println("%");

    // Send data to ESP32
    mySerial.print("Temperature: ");
    mySerial.print(temperature);
    mySerial.println("C");

    mySerial.print("Humidity: ");
    mySerial.print(humidity);
    mySerial.println("%");

    mySerial.print("Light level: ");
    mySerial.print(lightLevel);
    mySerial.println("%");

    delay(1000); // Wait for 1 second before next reading
}
