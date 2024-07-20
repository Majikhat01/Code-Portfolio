# ESP32-C3 MQTT Battery Test Project

## Overview

This project utilizes an ESP32-C3 microcontroller to monitor battery voltage, manage MQTT communications, and control a set of relays. It is designed for a pool table management system, allowing for remote monitoring and control via AWS IoT. 
The .ino file that's showcased was used to test the longevity of the system working on a single 18650 li-po battery. The system was able to last for 3 days before the battery was depleted.

## Project Functionality

- **Battery Monitoring**: Reads and processes battery voltage data using the ADC, ensuring accurate voltage measurements.
- **MQTT Communication**: Connects to AWS IoT to publish and subscribe to MQTT topics, enabling remote control and status updates.
- **Relay Control**: Manages relays to perform actions such as opening and closing gates for predefined durations.
- **WiFi and Time Synchronization**: Establishes and maintains WiFi connectivity, synchronizes with NTP servers to ensure accurate timekeeping.

## Key Features

1. **Battery Voltage Monitoring**: Accurate reading and reporting of battery voltage to ensure the system's power status is always known.
2. **MQTT Integration**: Seamless integration with AWS IoT for reliable message handling and remote control capabilities.
3. **Relay Management**: Efficient control of relays for managing physical devices, such as opening and closing gates.
4. **Deep Sleep Management**: Implements deep sleep functionality to conserve power when the device is not actively in use.

## Skills Demonstrated

- **Embedded Systems Programming**: Proficient use of C++ in developing firmware for the ESP32-C3 microcontroller.
- **IoT Communication**: Expertise in MQTT protocol and AWS IoT services for cloud-based device management.
- **Network Programming**: Advanced handling of WiFi connectivity and network time protocol (NTP) synchronization.
- **Power Management**: Implementation of power-saving techniques, including deep sleep mode to extend battery life.
- **Hardware Control**: Effective management of GPIO pins and relay control to interact with physical hardware components.

## Getting Started

1. Clone this repository.
2. Install the necessary libraries: `WiFi`, `PubSubClient`, `ArduinoJson`, `esp_sleep`.
3. Update the `secrets.h` file with your WiFi SSID, password, and AWS IoT credentials.
4. Compile and upload the code to your ESP32-C3 board using the Arduino IDE.

## Acknowledgments

- [ESP32 Arduino Core](https://github.com/espressif/arduino-esp32)
- [AWS IoT](https://aws.amazon.com/iot-core/)
