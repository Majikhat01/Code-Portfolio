#include "deviceControls.h"
#include "messageHandler.h"
#include <Arduino.h>

void openGate() {
  digitalWrite(RELAY1, HIGH);
  digitalWrite(RELAY4, HIGH);
  delay(250);
  digitalWrite(RELAY1, LOW);
  digitalWrite(RELAY4, LOW);
}

void closeGate() {
  digitalWrite(RELAY2, HIGH);
  digitalWrite(RELAY3, HIGH);
  delay(250);
  digitalWrite(RELAY2, LOW);
  digitalWrite(RELAY3, LOW);
}

void openGateGame() {
  openGate();
  publishMessage();
  delay(10000);
  closeGate();
}

void openGateHour() {
  openGate();
  publishMessage();
  delay(3600000);
  closeGate();
}