#ifndef PIPELINE
#define PIPELINE


#include <Arduino.h>
#include "machineEtat.hpp"
#include "ARGALI_PINOUT.hpp"
#include <vector>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

 enum ProcessStep {
        STEP_INIT,
        STEP_WAIT_SIM,
        STEP_CONFIG_CATM1,
        STEP_WAIT_CNACT,
        STEP_DONE
    };

enum PipelineCBOR{
        STEP_INIT_CBOR,
        STEP_VERIFIER_CONNEXION,
        STEP_OPEN_CONNEXION, 
        STEP_DEFINE_BYTE, 
        STEP_WRITE,
        STEP_CLOSE_CONNEXION,
        STEP_END

};
    
    void sendMinimalCBORMessage();
    void pipelineSwitchCBOR(const char* dataMessage);
    void repeatMachine();
    void sendMessageCBOR();
    boolean chrono(uint16_t time);
    void STEP_INIT_CBOR_FUNCTION(const char* dataMessage);

    extern std::vector<uint8_t> cborDataPipeline;
    extern ATCommandTask* taskCBOR_CASEND;
    extern PipelineCBOR currentStepCBOR;
    // extern ATCommandTask* currentTaskCBOR;
#endif