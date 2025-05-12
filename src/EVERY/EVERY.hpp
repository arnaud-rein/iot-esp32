#ifndef EVERY
#define EVERY


#include <Arduino.h>
#include "./../GNSS/SIM7080G_GNSS.hpp"
#include "./../ROM/ROM.hpp"
#include "./../ARGALI_PINOUT.hpp" 
#include "./../PIPELINE_GLOBAL.hpp"


void restartPipeline();
void coordPipeline();
#endif