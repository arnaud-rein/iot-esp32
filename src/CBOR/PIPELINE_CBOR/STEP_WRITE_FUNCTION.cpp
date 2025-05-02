// #include "./../pipeline.hpp"

// void STEP_WRITE_FUNCTION(){
//      // 5. Envoyer les octets CBOR
//      if(chrono(100)) {
//         Serial.println("[STEP_WRITE] ");
//         for (uint8_t byte : cborDataPipeline) {
//             Sim7080G.write(byte);
//         }

//         currentStepCBOR = STEP_CLOSE_CONNEXION;
//         PERIODE_CBOR = millis();
//     }
// }


#include "./../pipeline.hpp"

void STEP_WRITE_FUNCTION() {
    if (chrono(100)) {
        Serial.println("[STEP_WRITE] Envoi CBOR en cours...");

        // ✅ Envoi binaire CBOR
        Sim7080G.write(cborDataPipeline.data(), cborDataPipeline.size());

        Serial.println("[STEP_WRITE] ✅ CBOR envoyé");
        Serial.print("Octets : ");
        Serial.println(cborDataPipeline.size());

        // Passage à l'étape suivante
        currentStepCBOR = STEP_CLOSE_CONNEXION;
        PERIODE_CBOR = millis();
    }
}
