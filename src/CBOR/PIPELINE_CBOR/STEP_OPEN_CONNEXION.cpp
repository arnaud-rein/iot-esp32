#include "./../pipeline.hpp"


ATCommandTask taskCBOR_OPEN_CONNEXION("AT+CAOPEN=0,0,\"TCP\"," + (String) PINGGY_LINK + "," + (String) PINGGY_PORT, "OK", 15, 8000);
void STEP_OPEN_CONNEXION_FUNCTION(){

    if(chrono(100)) {
        Serial.println("[STEP_OPEN_CONNEXION] init");
        if(!taskCBOR_OPEN_CONNEXION.isFinished){
            machineCBOR.updateATState(taskCBOR_OPEN_CONNEXION); 
            currentTaskCBOR = &taskCBOR_OPEN_CONNEXION;
            PERIODE_CBOR = millis();
        }else{
            Serial.println("[STEP_OPEN_CONNEXION] success");
            currentStepCBOR = STEP_DEFINE_BYTE;
            PERIODE_CBOR = millis();
        }
    
    }
}