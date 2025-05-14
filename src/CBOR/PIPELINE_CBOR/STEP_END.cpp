#include "./../pipeline.hpp"

void STEP_END_FUNCTION()
{
    if (endCBOR)
    {
        Serial.println("[STEP_END] ");
        Serial.println("#######################################################END CBOR############################################");
        currentStepCBOR = STEP_INIT_CBOR;
        endCBOR = false;
        taskCBOR_CASEND = nullptr;
        command = "";
        cborDataPipeline.clear();
        // Marque le message comme traité et retire-le
        // if (!listeCoordonnees.empty())
        // {
        //     listeCoordonnees.front().endCBOR = true;
        //     listeCoordonnees.erase(listeCoordonnees.begin());
        // }
        if (nbCoordonnees > 0)
        {
            listeCoordonnees[0].endCBOR = true;
            // Supprimer le premier élément
            for (int i = 1; i < nbCoordonnees; ++i)
            {
                listeCoordonnees[i - 1] = listeCoordonnees[i];
            }
            nbCoordonnees--;
        }
    }
}