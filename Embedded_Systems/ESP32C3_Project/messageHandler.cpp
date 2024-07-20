#include "messageHandler.h"
#include "deviceControls.h"
#include "systemStatus.h"
#include "utils.h"

// Assuming that 'client' is instantiated and configured elsewhere, such as in the main .ino file
extern PubSubClient client;

// Handles incoming MQTT messages based on the topic and the payload provided
void messageHandler(char* topic, byte* payload, unsigned int length) {
  Serial.print("Incoming message on topic: ");
  Serial.println(topic);

  // Prepare the buffer for the incoming JSON payload
  char jsonBuffer[512];
  for (unsigned int i = 0; i < length; i++) {
    jsonBuffer[i] = (char)payload[i];
  }
  jsonBuffer[length] = '\0';  // Ensure null termination

  // Parse the JSON payload
  JsonDocument doc;
  DeserializationError error = deserializeJson(doc, jsonBuffer);
  if (error) {
    Serial.print("deserializeJson() failed: ");
    Serial.println(error.c_str());
    return;
  }

  // Handle commands based on JSON content
  if (doc.containsKey("command")) {
    String command = doc["command"].as<String>();
    if (command == "openGame") {
      openGateGame();
    } else if (command == "openHour") {
      openGateHour();
    } else if (command.startsWith("sleep:")) {
      int sleepMinutes = command.substring(command.indexOf(':') + 1).toInt();
      if (sleepMinutes > 0) {
          triggerSleep(sleepMinutes);
      } else {
          Serial.println("Invalid sleep duration provided.");
      }
    } else if (command == "systemVoltage") {
      float voltage = readBatteryVoltage();
      Serial.print("System voltage: ");
      Serial.println(voltage);
    }
  }
}

// Publishes general information messages to MQTT
void publishMessage() {
    String dateTime = getFormattedTime();
    if (dateTime.length() == 0) {
        Serial.println("Error: No valid time available for publishing message.");
        return;
    }
    
    float batteryVoltage = readBatteryVoltage();

    JsonDocument doc;
    doc["time"] = dateTime;
    doc["batteryVoltage"] = batteryVoltage;

    char jsonBuffer[256];
    size_t bytes = serializeJson(doc, jsonBuffer);
    jsonBuffer[bytes] = '\0'; // Ensure null termination
    Serial.println("Publishing message: ");
    Serial.println(jsonBuffer);

    if (!client.publish(AWS_IOT_PUBLISH_TOPIC, jsonBuffer)) {
        Serial.println("Publish failed");
    } else {
        Serial.println("Publish succeeded");
    }
}

// Publishes status-specific messages to MQTT
void publishStatusMessage(String message) {
    if (!client.publish(AWS_IOT_STATUS_TOPIC, message.c_str())) {
        Serial.println("Failed to publish status message");
    } else {
        Serial.println("Status message published");
    }
}
