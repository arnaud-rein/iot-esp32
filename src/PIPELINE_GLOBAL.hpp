#pragma once

#include <Arduino.h>
#include "ARGALI_PINOUT.hpp"
#include "SIM7080G_SERIAL.hpp"
#include "SIM7080G_CATM1.hpp"
#include "MachineEtat.hpp"
#include "./ROM/ROM.hpp"
#include "./GNSS/DisplayLatLng.hpp"
#include "./CBOR/pipeline.hpp"
#include "./EVERY/EVERY.hpp"
#include "./PIPELINE/GNSS/STEP_GNSS.hpp"
#include "./PIPELINE/4G/STEP_SEND_4G.hpp"

enum PipelineGLOBAL
{
    STEP_INIT_GLOBAL,
    STEP_GNSS,
    STEP_SEND_4G,
    STEP_END_GLOBAL

};

void step_gnss_function();
extern PipelineGLOBAL currentStepGLOBAL;
extern StepSend4GState currentStep4G;
extern bool afficherDepuisMemoire;

void pipelineGlobal();