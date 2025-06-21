#include <ESP32CAN.h>
#include <CAN_config.h>
#include <Arduino.h>

CAN_device_t CAN_cfg; // I don't think this is changeable.

void setup() {
  Serial.begin(115200); // Begin Serial.
  Serial.println("Serial up");
  CAN_cfg.speed = CAN_SPEED_100KBPS; // Set CAN speed.
  CAN_cfg.tx_pin_id = GPIO_NUM_4; // TX on Pin 4.
  CAN_cfg.rx_pin_id = GPIO_NUM_5; // RX on Pin 5.
  Serial.println("Speed and pins set");
  CAN_cfg.rx_queue = xQueueCreate(10, sizeof(CAN_frame_t));
  // ^Queue of length 10, and each element is a CAN frame (a message).
  ESP32Can.CANInit(); // Initialize CAN
  Serial.println("Queue and CAN up");
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
  Serial.println("Data set");

  ESP32Can.CANWriteFrame(&TXframe); // Send the frame.
  Serial.println("Frame sent");
  delay(2000); // Wait 2s before the next sending.
}