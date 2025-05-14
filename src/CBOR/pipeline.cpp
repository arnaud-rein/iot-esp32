#include "pipeline.hpp"

// DEFINITION DES VARIABLES INDISPENSABLE AU BON FONCTIONNEMENT DE CETTE PIPELINE
PipelineCBOR currentStepCBOR = STEP_INIT_CBOR;
std::vector<uint8_t> cborDataPipeline;
MachineEtat machineCBOR;
String command;
ATCommandTask *taskCBOR_CASEND = nullptr;
boolean endCBOR = true;
boolean resetCommandCEREG = false;
boolean resetCommandOPEN_CONNEXION = false;
boolean resetCommandCLOSE_CONNEXION = false;

ATCommandTask *currentTaskCBOR = nullptr;

// PIPELINE
void pipelineSwitchCBOR(const char *dataMessage)
{

    switch (currentStepCBOR)
    {

    case STEP_INIT_CBOR:
        STEP_INIT_CBOR_FUNCTION(dataMessage);
        break;

    case STEP_VERIFIER_CONNEXION:
        STEP_VERIFIER_CONNEXION_FUNCTION();
        break;

    case STEP_OPEN_CONNEXION:
        STEP_OPEN_CONNEXION_FUNCTION();
        break;

    case STEP_DEFINE_BYTE:
        STEP_DEFINE_BYTE_FUNCTION();
        break;

    case STEP_WRITE:
        STEP_WRITE_FUNCTION();
        break;

    case STEP_CLOSE_CONNEXION:
        STEP_CLOSE_CONNEXION_FUNCTION();
        break;

    case STEP_END:
        STEP_END_FUNCTION();
        break;
    }
}

boolean chrono(uint16_t time)
{
    return ((millis() - PERIODE_CBOR) > time);
}
