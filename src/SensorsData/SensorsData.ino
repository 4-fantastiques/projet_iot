#include <TH02_dev.h>
#include "Arduino.h"
#include "Wire.h"
#include "THSensor_base.h"

#define buttonRedPin 5
#define buttonGreenPin 4
#define LIGHT_SENSOR_PIN A3
#define SERIAL_BAUD_RATE 9600

int buttonRedState = 0;
int buttonGreenState = 0;

void setup()
{
    pinMode(buttonRedPin, INPUT);
    pinMode(buttonGreenPin, INPUT);
    Serial.begin(SERIAL_BAUD_RATE); // Start serial communication

    delay(150); // Wait for voltage to stabilize
    TH02.begin();
    delay(100);

    Serial.println("TH02_dev is available.\n");
}

void loop()
{
    buttonRedState = digitalRead(buttonRedPin);
    buttonGreenState = digitalRead(buttonGreenPin);

    if (buttonRedState == LOW)
    {
        Serial.println("Button Red is pressed");
    }
    else
    {
        Serial.println("Button Red is not pressed");
    }

    if (buttonGreenState == LOW)
    {
        Serial.println("Button Green is pressed");
    }
    else
    {
        Serial.println("Button Green is not pressed");
    }

    // Read light sensor value and map it to percentage
    int rawLightValue = analogRead(LIGHT_SENSOR_PIN);
    int lightLevel = map(rawLightValue, 0, 1023, 0, 100);

    // Read temperature and humidity from TH02 sensor
    float temperature = TH02.ReadTemperature();
    float humidity = TH02.ReadHumidity();

    // Print temperature and humidity values to serial
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println("C");

    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println("%");

    // Print light level to serial
    Serial.print("Light level: ");
    Serial.print(lightLevel);
    Serial.println("%");

    delay(1000); // Wait for 1 second before next reading
}
