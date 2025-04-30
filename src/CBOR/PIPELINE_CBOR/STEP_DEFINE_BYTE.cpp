#include "./../pipeline.hpp"

void STEP_DEFINE_BYTE_FUNCTION(){
    if(chrono(1000)) {
        Serial.println("[STEP_DEFINE_BYTE] init");
        if(!taskCBOR_CASEND->isFinished){
            machineCBOR.updateATState(*taskCBOR_CASEND); 
            PERIODE_CBOR = millis();
        }else{
            Serial.println("[STEP_DEFINE_BYTE] success");
            currentStepCBOR = STEP_WRITE;
            PERIODE_CBOR = millis();
        }

    }
}