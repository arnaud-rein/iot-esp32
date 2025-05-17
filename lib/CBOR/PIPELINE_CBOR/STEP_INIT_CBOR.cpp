#include "pipeline.hpp"

void STEP_INIT_CBOR_FUNCTION(const char *dataMessage)
{
    if (chrono(100))
    {
        // Serial.println("[STEP_INIT_CBOR] ");
        const char *message = dataMessage;
        Serial.println("[STEP_INIT_CBOR] message : " + String(message));
        // json j = message;
        json j = json::parse(message);

        // 2. Convertir en CBOR
        cborDataPipeline = json::to_cbor(j);
        // 🔍 LOG HEXA CBOR
        // Serial.println("[CBOR DUMP]");
        for (uint8_t b : cborDataPipeline)
        {
            if (b < 16)
                Serial.print("0");
            Serial.print(b, HEX);
            Serial.print(" ");
        }
        Serial.println(); // fin de ligne
        Serial.println(cborDataPipeline.size());
        Send_AT("AT+CACFG?", 500); // ou mieux : une ATCommandTask propre
        String newCommand = String("AT+CASEND=0,") + String(cborDataPipeline.size());
        Serial.println(newCommand);

        // Recréer l'objet taskCBOR_CASEND
        if (taskCBOR_CASEND != nullptr)
        {
            Serial.println("----------- taskCBOR_SEND ----------------------|||||||||||");
            delete taskCBOR_CASEND; // Si l'objet existait déjà, le supprimer pour éviter une fuite mémoire
        }
        taskCBOR_CASEND = new ATCommandTask(newCommand, ">", 15, 5000);

        currentStepCBOR = STEP_VERIFIER_CONNEXION;
        PERIODE_CBOR = millis();
        Serial.println("fin de step init __________________________==================>" + String(currentStepCBOR));
    }
}