#include "../../PIPELINE_GLOBAL.hpp"

StepSend4GState currentStep4G = STEP_SETUP_CATM1;

void step_send_4g_function()
{

    switch (currentStep4G)
    {
    case STEP_SETUP_CATM1:
        step_catm1_function();
        break;

    case STEP_SEND_CBOR:
        if (endCBOR)
        {
            Serial.println("Envoi des coordonnées au serveur distant +++++++++++++++++");

            String batch = "[";
            for (int i = 0; i < nbCoordonnees; ++i)
            {
                batch += listeCoordonnees[i].data;
                if (i < nbCoordonnees - 1)
                    batch += ",";
            }
            batch += "]";
            pipelineSwitchCBOR(batch.c_str());
        }
        else
        {
            period10min = millis();
            // listeCoordonnees.clear();
            nbCoordonnees = 0;
            currentStepGLOBAL = STEP_END_GLOBAL;
        }
        break;
    default:
        break;
    }
    // MessageCoord &msg = listeCoordonnees.front();
    // Serial.println(String(listeCoordonnees.size()) + " message(s) à envoyer");
    // Serial.println("Message à envoyer : " + msg.data);
    // pipelineSwitchCBOR(msg.data.c_str());
    // msg.endCBOR = false; // Marque comme en cours de traitement
    // Sinon, on attend que STEP_END_FUNCTION ait fini le traitement

    //     if (endCBOR)
    //     {
    //         Serial.println("Envoi des coordonnées au serveur distant +++++++++++++++++");

    //         String batch = "[";
    //         for (size_t i = 0; i < listeCoordonnees.size(); ++i)
    //         {
    //             batch += listeCoordonnees[i].data;
    //             if (i < listeCoordonnees.size() - 1)
    //                 batch += ",";
    //         }
    //         batch += "]";
    //         pipelineSwitchCBOR(batch.c_str());
    //     }
    //     else
    //     {
    //         period10min = millis();
    //         listeCoordonnees.clear();
    //         currentStepGLOBAL = STEP_END_GLOBAL;
    //     }
    // }
}