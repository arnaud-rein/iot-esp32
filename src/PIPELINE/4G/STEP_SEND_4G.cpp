#include "../../PIPELINE_GLOBAL.hpp"

void step_send_4g_function()
{
    if (oneRun)
    {
        setup_CATM1();
        oneRun = false;
    }

    if (!oneRun)
    {

        // MessageCoord &msg = listeCoordonnees.front();
        // Serial.println(String(listeCoordonnees.size()) + " message(s) à envoyer");
        // Serial.println("Message à envoyer : " + msg.data);
        // pipelineSwitchCBOR(msg.data.c_str());
        // msg.endCBOR = false; // Marque comme en cours de traitement
        // Sinon, on attend que STEP_END_FUNCTION ait fini le traitement

        if (endCBOR)
        {
            Serial.println("Envoi des coordonnées au serveur distant +++++++++++++++++");

            String batch = "[";
            for (size_t i = 0; i < listeCoordonnees.size(); ++i)
            {
                batch += listeCoordonnees[i].data;
                if (i < listeCoordonnees.size() - 1)
                    batch += ",";
            }
            batch += "]";
            pipelineSwitchCBOR(batch.c_str());
        }
        else
        {
            period10min = millis();
            listeCoordonnees.clear();
            currentStepGLOBAL = STEP_END_GLOBAL;
        }
    }
}