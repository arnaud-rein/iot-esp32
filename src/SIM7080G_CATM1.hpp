#ifndef SIM7080G_CATM1
#define SIM7080G_CATM1

#include <Arduino.h>
#include "ARGALI_PINOUT.hpp"
#include "SIM7080G_SERIAL.hpp"
#include "CBOR/pipeline.hpp"
#include "PIPELINE_GLOBAL.hpp"

void setup_CATM1();

void loop_CATM1();

void step_catm1_function();

// void cnactNumber(String dataLTE);
String findSelect(String data, String nameStart, int numberPassAfterNameStart, String symbolToSelectStart, String symbolToEnd);

void period10000function();

#endif
