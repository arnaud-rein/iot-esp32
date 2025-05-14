#include "PIPELINE_GLOBAL.hpp"

PipelineGLOBAL currentStepGLOBAL = STEP_INIT_GLOBAL;
// bool afficherDepuisMemoire = false;
// bool oneRun = true;

// PIPELINE
void pipelineGlobal()
{

  switch (currentStepGLOBAL)
  {

  case STEP_INIT_GLOBAL:
    Serial.println("---------------------- Lancement Pipelie GLOBAL -------------------------------");
    currentStepGLOBAL = STEP_GNSS;
    break;

  case STEP_GNSS:
    step_gnss_function();
    break;

  case STEP_SEND_4G:
    step_send_4g_function();
    break;

  case STEP_END_GLOBAL:
    Serial.println("===================================== STEP_END_GLOBAL =====================================");
    if ((millis() - period10min) > 10000)
    {
      endCBOR = true;
      currentStepGLOBAL = STEP_INIT_GLOBAL;
    }
    break;
  }
}