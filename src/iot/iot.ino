#include "libraries/ButtonModule/ButtonModule.h"
#include "libraries/BuzzerModule/BuzzerModule.h"
#include "libraries/LedModule/LedModule.h"
#include "libraries/LightSensor/LightSensor.h"
#include "libraries/OledModule/OledModule.h"
#include "libraries/SoundSensor/SoundSensor.h"
#include "libraries/TH02Module/TH02Module.h"
#include "Arduino.h"
#include <SoftwareSerial.h>
#include "U8glib.h" // U8g library

#define buttonRedPin 5
#define buttonGreenPin 4
#define SOUND_SENSOR_PIN A2
#define LIGHT_SENSOR_PIN A3
#define SERIAL_BAUD_RATE 9600
#define RX_PIN 8
#define TX_PIN 9
#define BUZZER_PIN 2
#define LED_RED_PIN 6
#define LED_GREEN_PIN 5

ButtonModule buttonRed(buttonRedPin);
ButtonModule buttonGreen(buttonGreenPin);
LightSensorModule lightSensor(LIGHT_SENSOR_PIN);
SoundSensorModule soundSensor(SOUND_SENSOR_PIN);
TH02Module th02Sensor;
OLEDModule oled; // Création d'une instance d'OLEDModule

SoftwareSerial mySerial(RX_PIN, TX_PIN); // RX, TX

void show_empty_screen()
{
    oled.showEmptyScreen();
}

void setup()
{
    Serial.begin(SERIAL_BAUD_RATE);   // Start serial communication
    mySerial.begin(SERIAL_BAUD_RATE); // Start software serial communication
    buttonRed.init();
    buttonGreen.init();
    lightSensor.init();
    soundSensor.init();
    th02Sensor.init();
    oled.init(); // Initialisation de l'écran OLED

    pinMode(BUZZER_PIN, OUTPUT);    // Configurer la broche du buzzer comme sortie
    pinMode(LED_RED_PIN, OUTPUT);   // Configurer la broche de la LED rouge comme sortie
    pinMode(LED_GREEN_PIN, OUTPUT); // Configurer la broche de la LED verte comme sortie

    digitalWrite(BUZZER_PIN, LOW);    // Assurez-vous que le buzzer est désactivé au départ
    digitalWrite(LED_RED_PIN, LOW);   // Assurez-vous que la LED rouge est éteinte au départ
    digitalWrite(LED_GREEN_PIN, LOW); // Assurez-vous que la LED verte est éteinte au départ

    Serial.println("TH02_dev is available.\n");
}

void loop()
{
    buttonRed.update();
    buttonGreen.update();

    const char *redButtonState = buttonRed.isPressed() ? "Button Red: pressed" : "Button Red: not pressed";
    const char *greenButtonState = buttonGreen.isPressed() ? "Button Green: pressed" : "Button Green: not pressed";

    int lightLevel = lightSensor.getLightLevel();
    float temperature = th02Sensor.getTemperature();
    float humidity = th02Sensor.getHumidity();
    int soundLevel = soundSensor.getSoundLevel();

    // Afficher les valeurs sur l'OLED
    oled.displayValues(temperature, humidity, lightLevel, soundLevel);

    // Activer le buzzer et la LED verte si le bouton vert est pressé
    if (buttonGreen.isPressed())
    {
        tone(BUZZER_PIN, 500);             // Émettre un son de 500 Hz
        delay(100);                        // Maintenir le son pendant 100 ms
        noTone(BUZZER_PIN);                // Arrêter le son
        digitalWrite(LED_GREEN_PIN, HIGH); // Allumer la LED verte
    }
    else
    {
        digitalWrite(LED_GREEN_PIN, LOW); // Éteindre la LED verte
    }

    // Allumer la LED rouge si le bouton rouge est pressé
    if (buttonRed.isPressed())
    {
        digitalWrite(LED_RED_PIN, HIGH); // Allumer la LED rouge
    }
    else
    {
        digitalWrite(LED_RED_PIN, LOW); // Éteindre la LED rouge
    }

    // Print to serial monitor
    Serial.println(redButtonState);
    Serial.println(greenButtonState);
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println("C");
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println("%");
    Serial.print("Light level: ");
    Serial.print(lightLevel);
    Serial.println("%");
    Serial.print("Sound level: ");
    Serial.println(soundLevel);

    // Send data to ESP32
    mySerial.println(redButtonState);
    mySerial.println(greenButtonState);
    mySerial.print("Temperature: ");
    mySerial.print(temperature);
    mySerial.println("C");
    mySerial.print("Humidity: ");
    mySerial.print(humidity);
    mySerial.println("%");
    mySerial.print("Light level: ");
    mySerial.print(lightLevel);
    mySerial.println("%");
    mySerial.print("Sound level: ");
    mySerial.println(soundLevel);

    delay(1000); // Wait for 1 second before next reading
}
