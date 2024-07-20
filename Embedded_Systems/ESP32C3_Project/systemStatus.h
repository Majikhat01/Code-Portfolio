#ifndef SYSTEM_STATUS_H
#define SYSTEM_STATUS_H

// Includes only the essentials needed for declarations
#include <Arduino.h>  // Required for data types and Serial

// Declaration of functions that manage the system's status
float readBatteryVoltage();
void triggerSleep(int sleepMinutes);
void wakeUpProcedures();

#endif // SYSTEM_STATUS_H