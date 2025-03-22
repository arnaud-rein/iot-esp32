#include "./../pipeline.hpp"

void STEP_INIT_CBOR_FUNCTION(const char* dataMessage){
    if(chrono(100)) {
        Serial.println("[STEP_INIT_CBOR] ");
        const char* message = dataMessage;
        json j = message;

        // 2. Convertir en CBOR
        cborDataPipeline= json::to_cbor(j);
        Serial.println(cborDataPipeline.size());
        // Convertir la taille en String et concaténer correctement :
        String newCommand = String("AT+CASEND=0,") + String(cborDataPipeline.size());
        Serial.println(newCommand); 

        // Recréer l'objet taskCBOR_CASEND
        if (taskCBOR_CASEND != nullptr) {
            delete taskCBOR_CASEND;  // Si l'objet existait déjà, le supprimer pour éviter une fuite mémoire
        }
        taskCBOR_CASEND = new ATCommandTask(newCommand, ">", 15, 3000);

        currentStepCBOR = STEP_VERIFIER_CONNEXION;
        PERIODE_CBOR = millis();
    }
}