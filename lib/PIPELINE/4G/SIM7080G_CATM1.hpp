#ifndef SIM7080G_CATM1
#define SIM7080G_CATM1

#include <Arduino.h>
#include "GLOBALS.hpp"
#include "SIM7080G_SERIAL.hpp"
#include "CBOR/pipeline.hpp"
#include "PIPELINE_GLOBAL.hpp"

void step_catm1_function();
String findSelect(String data, String nameStart, int numberPassAfterNameStart, String symbolToSelectStart, String symbolToEnd);
#endif
