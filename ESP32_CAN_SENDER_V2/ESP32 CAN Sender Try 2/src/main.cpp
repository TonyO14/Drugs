#include <ESP32CAN.h>
#include <CAN_config.h>
#include <Arduino.h>

void blink(); // A function to blink.

CAN_device_t CAN_cfg; // I don't think this is changeable.

void setup() {
  Serial.begin(115200); // Begin Serial.
  Serial.println("Serial up");
  CAN_cfg.speed = CAN_SPEED_500KBPS; // Set CAN speed.
  CAN_cfg.tx_pin_id = GPIO_NUM_21; // TX on Pin 21.
  CAN_cfg.rx_pin_id = GPIO_NUM_22; // RX on Pin 22.
  Serial.println("Speed and pins set");
  CAN_cfg.rx_queue = xQueueCreate(10, sizeof(CAN_frame_t));
  // ^Queue of length 10, and each element is a CAN frame (a message).
  ESP32Can.CANInit(); // Initialize CAN
  Serial.println("Queue and CAN up");

  // Initialize LED pin
  pinMode(GPIO_NUM_2, OUTPUT); // Set GPIO 2 as output for LED.
}

void loop() {
  // Don't care about receiving for now.
  CAN_frame_t TXframe; // Transmitting frame creation.
  Serial.println("Made frame");
  TXframe.FIR.B.FF = CAN_frame_std; // Keep it standard.
  TXframe.MsgID = 1; // ID is 1.
  TXframe.FIR.B.DLC = 8; // Data is 8 bytes.
  TXframe.data.u8[0] = 'd'; // Spell out "doughnut".
  TXframe.data.u8[1] = 'o';
  TXframe.data.u8[2] = 'u';
  TXframe.data.u8[3] = 'g';
  TXframe.data.u8[4] = 'h';
  TXframe.data.u8[5] = 'n';
  TXframe.data.u8[6] = 'u';
  TXframe.data.u8[7] = 't';

  // Instead of donut, send two bytes of 100 and 10.
  // TXframe.FIR.B.DLC = 2; // Data length code is 2 bytes.
  // TXframe.data.u8[0] = 100; // First byte is 100.
  // TXframe.data.u8[1] = 10; // Second byte is 10.

  Serial.println("Data set");

  ESP32Can.CANWriteFrame(&TXframe); // Send the frame.
  Serial.println("Frame sent");
  // delay(2000); // Wait 2s before the next sending. Comment out optionally.

  blink();
}

void blink() {
  digitalWrite(GPIO_NUM_2, HIGH); // Turn on LED.
  delay(500); // Wait 500ms.
  digitalWrite(GPIO_NUM_2, LOW); // Turn off LED.
  delay(500); // Wait 500ms.
}