#include <Arduino.h>
#include "WiFi.h"            // Make sure the WiFi library is included if used for WiFi functions
#include "messageHandler.h"  // Ensure that this header has the publishStatusMessage function declared
#include "systemStatus.h"
#include "utils.h"

const int BATTERY_PIN = 0; // Pin definition for reading battery voltage

float readBatteryVoltage() {
    uint32_t Vbatt = 0;
    for (int i = 0; i < 16; i++) {
        Vbatt += analogRead(BATTERY_PIN); // Sum raw ADC values
    }
    Vbatt /= 16; // Average the ADC values

    // Convert the average raw ADC value to a voltage assuming the ADC reference is 3.3V and 12-bit resolution (4096 levels)
    float adcVoltage = Vbatt * (3.3 / 4095.0);

    // Correct for voltage divider
    // R1 = 150kΩ, R2 = 68kΩ
    // Vin = Vout * ((R1 + R2) / R2)
    float correctedVoltage = adcVoltage * ((150000.0 + 68000.0) / 68000.0) + 0.61;

    // Output for debugging
    Serial.print("Average Raw ADC Value: ");
    Serial.println(Vbatt);
    Serial.print("ADC Input Voltage: ");
    Serial.println(adcVoltage, 3); // Show more decimal places for precision
    Serial.print("Calculated Battery Voltage: ");
    Serial.println(correctedVoltage, 2);

    return correctedVoltage;
}

void triggerSleep(int sleepMinutes) {
    uint64_t sleepDurationUs = sleepMinutes * 60 * 1000000ULL; // Convert minutes to microseconds
    Serial.print("Preparing to go to sleep for ");
    Serial.print(sleepMinutes);
    Serial.println(" minute(s).");

    String sleepMessage = "Going to deep sleep for " + String(sleepMinutes) + " minute(s).";
    publishStatusMessage(sleepMessage);
    delay(1000);
    esp_sleep_enable_timer_wakeup(sleepDurationUs);
    Serial.println("Sleep mode activated.");
    esp_deep_sleep_start();
}

void wakeUpProcedures() {
  // Re-enable WiFi
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.println("Wireless connections re-enabled. Reconnecting...");
}
