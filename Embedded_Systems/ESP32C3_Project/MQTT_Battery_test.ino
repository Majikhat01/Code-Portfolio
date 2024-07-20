#include <Arduino.h>
#include <PubSubClient.h>
#include "time.h"
#include <esp_sleep.h>

#include "utils.h"
#include "messageHandler.h"
#include "deviceControls.h"
#include "systemStatus.h"

RTC_DATA_ATTR int bootCount = 0;

void setup() {
  Serial.begin(115200);

  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);
  pinMode(RELAY3, OUTPUT);
  pinMode(RELAY4, OUTPUT);
  digitalWrite(RELAY1, LOW);
  digitalWrite(RELAY2, LOW);
  digitalWrite(RELAY3, LOW);
  digitalWrite(RELAY4, LOW);

  pinMode(A0, INPUT);         // ADC

  ++bootCount;
  Serial.println("Boot number: " + String(bootCount));

  // Wake-up procedures
  if (esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_TIMER) {
    String message = "Woke up from sleep.";
    publishStatusMessage(message);
  }
  
  wakeUpProcedures();
  connectMQTT();
}

void loop() {
  ensureConnections();
  client.loop();
  delay(100);  // Delay to prevent too frequent looping
}
