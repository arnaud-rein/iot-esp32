#include "./../pipeline.hpp"

void STEP_END_FUNCTION()
{
    if (endCBOR)
    {
        Serial.println("[STEP_END] ");
        Serial.println("#######################################################END CBOR############################################");
        premierTour = false;
        END_CBOR_SEND = true;
        currentStepCBOR = STEP_INIT_CBOR;
        endCBOR = false;
        taskCBOR_CASEND = nullptr;
        command = "";
        cborDataPipeline.clear();
        // Marque le message comme traité et retire-le
        if (!listeCoordonnees.empty())
        {
            listeCoordonnees.front().endCBOR = true;
            listeCoordonnees.erase(listeCoordonnees.begin());
        }
    }
}