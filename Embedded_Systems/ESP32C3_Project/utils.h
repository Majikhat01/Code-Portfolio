#ifndef UTILS_H
#define UTILS_H

#include <Arduino.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "WiFi.h"

#include "secrets.h"
#include "messageHandler.h"
#include "deviceControls.h"
#include "systemStatus.h"

// Constants for time management
extern const long uS_TO_S_FACTOR;
extern const long TIME_TO_SLEEP;

// MQTT Topics
extern const char AWS_IOT_PUBLISH_TOPIC[];
extern const char AWS_IOT_STATUS_TOPIC[];
extern const char AWS_IOT_SUBSCRIBE_TOPIC[];

// Network and MQTT clients
extern WiFiClientSecure net;
extern PubSubClient client;

// NTP and time management
extern const char* ntpServer;
extern const long gmtOffset_sec;
extern const int daylightOffset_sec;

// Function Declarations
String getFormattedTime();
void ensureConnections();
void connectWiFi();
void connectMQTT();
void setupAWSIoT();
void waitForSync();
bool timeIsSynchronized();
void printMQTTState(int state);

#endif // UTILS_H
