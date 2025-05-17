#include "PIPELINE_GLOBAL.hpp"

void step_compose_json_function()
{
    // String imei = readSimIdFromEEPROM(); // ou getEsp32Id();

    // Création du JSON string pour chaque coordonnée à partir de dataGNSS
    for (int i = 0; i < nbCoordonnees; ++i)
    {
        // Récupération des coordonnées depuis dataGNSS
        String latitude = dataGNSS[i].gnss.coordonnees.latitude.full;
        String longitude = dataGNSS[i].gnss.coordonnees.longitude.full;

        listeCoordonnees[i].data = String("{\"name\":\"") + imei +
                                   "\",\"position\":{\"latitude\":" + latitude +
                                   ",\"longitude\":" + longitude + "}}";
    }
    // Création du tableauJSONString JSON (tableau de messages)
    tableauJSONString = "[";
    for (int i = 0; i < nbCoordonnees; ++i)
    {
        tableauJSONString += listeCoordonnees[i].data;
        if (i < nbCoordonnees - 1)
            tableauJSONString += ",";
    }
    tableauJSONString += "]";

    Serial.println("Envoi des coordonnées au serveur distant +++++++++++++++++");
    Serial.println(tableauJSONString);

    currentStepGLOBAL = STEP_SEND_4G;

    // Envoi ou traitement du tableauJSONString
    // pipelineSwitchCBOR(tableauJSONString.c_str());
}