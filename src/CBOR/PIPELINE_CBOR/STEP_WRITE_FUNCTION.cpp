#include "./../pipeline.hpp"

void STEP_WRITE_FUNCTION(){
     // 5. Envoyer les octets CBOR
     if(chrono(100)) {
        Serial.println("[STEP_WRITE] ");
        for (uint8_t byte : cborDataPipeline) {
            Sim7080G.write(byte);
        }

        currentStepCBOR = STEP_CLOSE_CONNEXION;
        PERIODE_CBOR = millis();
    }
}