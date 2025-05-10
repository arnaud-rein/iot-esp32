#include "./../pipeline.hpp"

void STEP_DEFINE_BYTE_FUNCTION(){
    if(chrono(1000)) {
        Serial.println("[STEP_DEFINE_BYTE] init [STEP_DEFINE_BYTE] init [STEP_DEFINE_BYTE] init [STEP_DEFINE_BYTE] init [STEP_DEFINE_BYTE] init ");
        if(!taskCBOR_CASEND->isFinished){
            // Serial.println("&&&&&&&&&&&&&&&&&&&&&&&&&&   dans taskCBOR &&&&&&&&&&&&&&&&&&");
            machineCBOR.updateATState(*taskCBOR_CASEND); // taskCBOR_CASEND = new ATCommandTask(newCommand, ">", 15, 3000);  newCommand = AT+CASEND=0,5

            PERIODE_CBOR = millis();
        }else{
            Serial.println("[STEP_DEFINE_BYTE] success");
            currentStepCBOR = STEP_WRITE;
            PERIODE_CBOR = millis();
        }

    }
}