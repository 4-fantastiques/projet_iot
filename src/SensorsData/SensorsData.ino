#include <TH02_dev.h>
#include "Arduino.h"
#include "Wire.h"
#include "THSensor_base.h"

#define Serial Serial

#ifdef __AVR__
    #include <SoftwareSerial.h>
    SoftwareSerial SSerial(2, 3); // RX, TX
    #define COMSerial Serial
    #define Serial Serial
    TH02_dev TH02;
#endif

#ifdef ARDUINO_SAMD_VARIANT_COMPLIANCE
    #define COMSerial Serial1
    #define Serial SerialUSB
    TH02_dev TH02;
#endif

#ifdef ARDUINO_ARCH_STM32F4
    #define COMSerial Serial
    #define Serial SerialUSB
    TH02_dev TH02;
#endif

int light_sensor = A3; 

void setup() {
    Serial.begin(9600);        // start serial for output

    Serial.println("****TH02_dev demo by seeed studio****\n");
    /* Power up,delay 150ms,until voltage is stable */
    delay(150);
    /* Reset HP20x_dev */
    TH02.begin();
    delay(100);

    /* Determine TH02_dev is available or not */
    Serial.println("TH02_dev is available.\n");
}


void loop() {
    ///////////////////////////////////////////////////////
    /////////////// Initalisation variables ///////////////
    ///////////////////////////////////////////////////////

    // Capteur de luminosité
    int raw_light = analogRead(light_sensor); // read the raw value from light_sensor pin (A3)
    int light = map(raw_light, 0, 1023, 0, 100); // map the value from 0, 1023 to 0, 100

    // Capteur de température - Humidité
    float temper = TH02.ReadTemperature();
    float humidity = TH02.ReadHumidity();

    ///////////////////////////////////////////////////////
    ///////////////////// Sortie Série ////////////////////
    ///////////////////////////////////////////////////////


    // Capteur de température - Humidité
    Serial.print("Temperature: ");
    Serial.print(temper);
    Serial.println("C\r\n");
    
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println("%\r\n");

    // Capteur de luminosité

    Serial.print("Light level: ");
    Serial.print(light);
    Serial.println("%\r\n");

    delay(1000);
}
