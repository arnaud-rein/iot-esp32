#include "PIPELINE_GLOBAL.hpp"

ATCommandTask gnssPowerOnCommand("AT+CGNSPWR=1", "OK", 6, 4000); // Commande d’activation GNSS
ATCommandTask gnssInfCommand("AT+CGNSINF=?", "OK", 6, 4000);     // Commande d’activation GNSS
ATCommandTask gnssPowerOffCommand("AT+CGNSPWR=0", "OK", 3, 2000);

MachineEtat machineGNSS; // Instance de la machine d’état
bool afficherDepuisMemoire = false;
uint8_t iterationList = 0;

enum StepGNSSState
{
    GNSS_POWER_ON,
    GNSS_INFO,
    GNSS_POWER_OFF,
    GNSS_DONE
};

StepGNSSState gnssStepState = GNSS_POWER_ON;

// Définition de la fonction callback à part
void gnssErrorPowerOn(ATCommandTask &task)
{
    Serial.println("[ERROR] Problème avec " + String(task.command));
    Serial.println("[ERROR] Aucun gestionnaire d'erreur spécifique");
}

void step_gnss_function()
{
    Serial.println("[STEP_GNSS]");
    switch (gnssStepState)
    {
    case GNSS_POWER_ON:
    {

        // Serial.println("okPowerOn = " + String(okPowerOn));
        // TO DO : a remettre dans bool
        // machineGNSS.updateATState(gnssPowerOnCommand);
        gnssPowerOnCommand.onErrorCallback = gnssErrorPowerOn;
        if (machineGNSS.updateATState(gnssPowerOnCommand))
        {
            Serial.println("------>GNSS_POWER_ON[OK]");
            gnssPowerOnCommand.state = IDLE;
            gnssStepState = GNSS_INFO;
        }
    }
    break;

    case GNSS_INFO:
    {

        // Ici tu peux envoyer les commandes d'info GNSS
        // Send_AT("AT+CGNSTST=1", 500);
        Serial.println(Send_AT("AT+CGNSMOD?"));
        Serial.println(Send_AT("AT+CGNSPWR?", 500));
        String response = Send_AT("AT+CGNSINF", 2000);
        // Serial.println(response);

        if (nbCoordonnees < 10 && (millis() - periodGNSS) > 3000)
        {
            periodGNSS = millis();
            Gnss gnss = getGNSSValid();
            if (gnss.isValid)
            {
                addGNSSInDataGNSS(gnss);
            }
            // DisplayLatLngInfo(&afficherDepuisMemoire);
        }
        else if (nbCoordonnees >= 10)
        {
            // Serial.println("Trop de messages dans la liste, on ne peut pas en ajouter d'autres");
            gnssStepState = GNSS_POWER_OFF;
        }
        break;
    }

    case GNSS_POWER_OFF:
    {
        bool okPowerOff = machineGNSS.updateATState(gnssPowerOffCommand);
        if (okPowerOff)
        {
            Serial.print("-->GNSS_POWER_OFF[OK]");
            gnssPowerOffCommand.state = IDLE;
            gnssStepState = GNSS_DONE;
        }
        break;
    }

    case GNSS_DONE:
    {
        currentStepGLOBAL = STEP_COMPOSE_JSON;
        gnssStepState = GNSS_POWER_ON;
        break;
    }
    }
}