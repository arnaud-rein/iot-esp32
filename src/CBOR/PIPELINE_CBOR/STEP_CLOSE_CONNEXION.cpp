#include "./../pipeline.hpp"
ATCommandTask taskCBOR_CLOSE("AT+CACLOSE=0", "OK", 15, 100);
void STEP_CLOSE_CONNEXION_FUNCTION(){
    if(chrono(100)) {
        Serial.println("[STEP_CLOSE_CONNEXION] init");
        if(!taskCBOR_CLOSE.isFinished){
            machineCBOR.updateATState(taskCBOR_CLOSE);
        }else{
            Serial.println("[STEP_CLOSE_CONNEXION] success");
            currentStepCBOR = STEP_END;
        }
        
    }
}