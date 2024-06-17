#include <HardwareSerial.h>

// Déclaration de la seconde interface série
HardwareSerial mySerial(2); // UART2

void setup() {
  // Initialisation de la communication série pour la console
  Serial.begin(9600);
  // Initialisation de la communication série avec l'Arduino Uno
  mySerial.begin(9600, SERIAL_8N1, 16, 17); // UART2: RX=16, TX=17
}

void loop() {
  // Vérification si des données sont disponibles
  if (mySerial.available()) {
    String received = mySerial.readStringUntil('\n');
    // Affichage des données reçues sur le moniteur série de l'ESP32
    Serial.println(received);
  }
  delay(100);
}
