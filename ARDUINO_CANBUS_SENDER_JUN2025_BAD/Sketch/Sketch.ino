#include <Arduino.h>
#include <CAN.h>

#define TX_PIN 5 // TX pin: 5
#define RX_PIN 4 // RX pin: 4

// Declare some functions that I can use to hotswap between
// flashing the receiver board and flashing the sender board
void SendCan();
void ReceiveCan();
// ---------------------

void setup() {



  CAN.setPins(RX_PIN, TX_PIN); // Set the CAN pins.
  CAN.begin(500000); // Begin CAN at 500k baud rate.

  // LED Indicator
  pinMode(13, OUTPUT); // LED on pin 13. This is the internal LED.

}

void loop() { //Toggle whatever function depending on board.
  //SendCan();
  ReceiveCan();

}

void SendCan() {
  CAN.beginPacket(0x12); // Set the CAN ID to be 0x12.
  CAN.write(0x56); // Encode 86 in the payload.
  CAN.endPacket(); // End the CAN packet and send.
  delay(800);
}

void ReceiveCan() {
 int packetSize = CAN.parsePacket();

  if (packetSize) { // If a packet comes in.
      for (int i=1; i<5; i++) {
        digitalWrite(13, HIGH);
        delay(50); 
        digitalWrite(13, LOW);
        delay(50); // Flicker the LED
      }
  }
}
