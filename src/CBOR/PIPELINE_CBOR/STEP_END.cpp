#include "./../pipeline.hpp"


void STEP_END_FUNCTION(){
    if(endCBOR) {
        Serial.println("[STEP_END] ");
        Serial.println("#######################################################END CBOR############################################");
        endCBOR = false; 
        END_CBOR_SEND = true; 
    }
}