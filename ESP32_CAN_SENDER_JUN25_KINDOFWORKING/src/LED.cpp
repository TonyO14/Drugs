#ifdef TEST_FILE

#include <Arduino.h>

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("LED Blink Test Starting...");
  
  // Pin 2 is built-in LED for most ESP32 boards
  pinMode(2, OUTPUT);
  
  Serial.println("Setup complete - LED should start blinking");
}

void loop() {
  Serial.println("LED ON");
  digitalWrite(2, HIGH);
  delay(500);
  
  Serial.println("LED OFF");
  digitalWrite(2, LOW);
  delay(500);
}

#endif