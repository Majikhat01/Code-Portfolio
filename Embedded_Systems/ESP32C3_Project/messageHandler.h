#ifndef MESSAGE_HANDLER_H
#define MESSAGE_HANDLER_H

#include <ArduinoJson.h> // Required for JsonDocument
#include "PubSubClient.h" // Required for PubSubClient class
#include <Arduino.h> // Required for String type

// Declaration of external PubSubClient object
extern PubSubClient client;

// Function declarations
void messageHandler(char* topic, byte* payload, unsigned int length);
void publishMessage();
void publishStatusMessage(String message);

#endif // MESSAGE_HANDLER_H
