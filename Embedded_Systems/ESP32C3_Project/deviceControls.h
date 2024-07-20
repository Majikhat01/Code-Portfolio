#ifndef DEVICE_CONTROLS_H
#define DEVICE_CONTROLS_H

const int RELAY1 = 4; // Assuming RELAY1 is connected to pin 4
const int RELAY2 = 5; // Assuming RELAY2 is connected to pin 5
const int RELAY3 = 6; // Assuming RELAY3 is connected to pin 6
const int RELAY4 = 7; // Assuming RELAY4 is connected to pin 7

void openGate();
void closeGate();
void openGateGame();
void openGateHour();

#endif // DEVICE_CONTROLS_H