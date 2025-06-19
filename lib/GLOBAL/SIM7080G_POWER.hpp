#ifndef POWER_HPP
#define POWER_HPP

#include <Arduino.h>
#include "GLOBALS.hpp"
#include "SIM7080G_SERIAL.hpp"

// Déclaration de la fonction
void turn_on_SIM7080G();
void turn_off_SIM7080G();
void reboot_SIM7080G();
String getBatteryLevel();
#endif // POWER_HPP
