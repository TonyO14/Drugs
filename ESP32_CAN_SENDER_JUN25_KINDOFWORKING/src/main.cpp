
#include <Arduino.h>
#include <CAN.h>

#define TX_PIN 14 // TX pin: 5
#define RX_PIN 15 // RX pin: 4

// Declare some functions that I can use to hotswap between
// flashing the receiver board and flashing the sender board
void SendCan();
void ReceiveCan();
// ---------------------

void setup() {



  CAN.setPins(RX_PIN, TX_PIN); // Set the CAN pins.
  CAN.begin(100E3); // Begin CAN at 100k baud rate.

  // LED Indicator
  pinMode(2, OUTPUT); // LED on pin 2. This is the internal LED.

}

void loop() { //Toggle whatever function depending on board.
  SendCan();
  //ReceiveCan();

}

void SendCan() {
  CAN.beginPacket(0x23); // Set the CAN ID to be 0x12.
  CAN.write(10); // Encode 10 in the payload.
  CAN.endPacket(); // End the CAN packet and send.
  delay(800);
  digitalWrite(2, HIGH); // Turn on the LED.
  delay(100);
  digitalWrite(2, LOW); // Turn off the LED.
  delay(100);
}

void ReceiveCan() {
 int packetSize = CAN.parsePacket();

  if (packetSize) { // If a packet comes in.
      for (int i=1; i<5; i++) {
        digitalWrite(2, HIGH);
        delay(50); 
        digitalWrite(2, LOW);
        delay(50); // Flicker the LED
      }
  }
}
