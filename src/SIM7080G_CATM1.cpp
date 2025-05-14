#include "SIM7080G_CATM1.hpp"

ATCommandTask taskCATM1_CEREG("AT+CEREG?", "+CEREG: 0,5", 15, 100);
ATCommandTask taskCATM1_CGDCONT("AT+CGDCONT=1,\"IP\",\"iot.1nce.net\"", "OK", 10, 100);
MachineEtat machineCATM1;

enum StepCATM1State
{
    CATM1_POWER_ON,
    CATM1_CGDCONT,
    CATM1_INFO,
    CATM1_POWER_OFF,
    CATM1_DONE
};

StepCATM1State currentStepCATM1 = CATM1_POWER_ON;

void setup_CATM1()
{

    // see datasheet
    Send_AT("AT+CNMP=38");

    /*
    WARNING on the ARGALI SIM C3 V1.0 the SIMCOM processor used is
    SIM7080G-M that does not feature NB-IOT.
    1 -> CAT-M1 et 2 -> NB-IOT
    */
    Send_AT("AT+CMNB=1");

    // APP Network Deactive(PDP context)
    Send_AT("AT+CNACT=0,0");

    if (machineCATM1.updateATState(taskCATM1_CGDCONT))
    {
        // La commande AT+CGNAPN est utilisée pour configurer le nom du point d'accès (APN) pour la connexion de données.
        Send_AT("AT+CGNAPN");

        // La commande AT+CNCFG est spécifique à certains modules cellulaires
        // (comme SIMCom SIM7080G/SIM7600, etc.) et elle est utilisée pour
        // configurer les paramètres de connectivité réseau, en particulier pour le mode NB-IoT, LTE-M ou Cat-M1.
        // AT+CNCFG sert à configurer un profil de contexte PDP (Packet Data Protocol)
        // c’est-à-dire les paramètres permettant d’accéder à Internet via un réseau mobile.
        Send_AT("AT+CNCFG=0,1,iot.1nce.net");

        // La commande AT+CEREG sert à vérifier ou configurer l'enregistrement du module sur le réseau LTE (4G), plus précisément dans le mode E-UTRAN (réseau d'accès radio LTE).
        // Signification :
        // CEREG = Cellular Evolved REGistration (enregistrement sur le réseau LTE uniquement)
        if (machineCATM1.updateATState(taskCATM1_CEREG))
        {
            // APP Network Active (PDP context) pour avoir une adressee IP
            // You should wait for a valid response : +APP PDP: 0,ACTIVE
            String resultPDP = findSelect(Send_AT("AT+CNACT=0,1", 15000), "PDP", 4, ",", " ");
            if (resultPDP == "ACTIVE")
            {
                Serial.print("ACTIVE detecté");
            }

            // informations for you on CAT-M1 connexion
            Send_AT("AT+CGATT?");
            Send_AT("AT+CNACT?", 3000);
            String resultCNACT = findSelect(Send_AT("AT+CNACT?", 3000), "+CNACT:", 12, "\"", ".");
            if (resultCNACT == "10")
            {
                Serial.println("10 detecté");
            }
            Send_AT("AT+GSN");
            Send_AT("AT+CCID");
            Send_AT("AT+COPS?");
            Send_AT("AT+CEREG?");
            // signal quality
            Send_AT("AT+CSQ");
        }
    }

    /*
    We wait for the SIM7080G to register to the local 4G antenna
    Correct registration :
    AT+CEREG?
    +CEREG: 0,5
    */
}

void loop_CATM1() // vérifie que c'est bien connecté via la connexion = 5
{
    if (findSelect(Send_AT("AT+CEREG?"), "+CEREG:", 9, ",", " ") == "5")
    {
        Serial.println("5 condition");
        // TCP_send();
    }
    Send_AT("AT+CSQ");
    // csqNumber(Send_AT("AT+CSQ"));
}

void period10000function()
{
    if ((millis() - period100000) > 10000)
    {
        Serial.println("--");
        Serial.println("--");
        Serial.println("");
        Serial.print("[");
        Serial.print(millis());
        Serial.print("ms]");
        Serial.println("");
        Serial.println("--");
        Serial.println("--");
        period100000 = millis();
    }
}

String findSelect(String data, String nameStart, int numberPassAfterNameStart, String symbolToSelectStart, String symbolToEnd)
{
    Serial.print("millis de findSelect" + (String)millis());
    int indexStart = data.indexOf(nameStart, 0);
    int indexAfterStart = indexStart + numberPassAfterNameStart;
    int indexSymbolStart = data.indexOf(symbolToSelectStart, indexAfterStart);
    int numberBetween_symbolStart_symbolEnd = data.indexOf(symbolToEnd, indexSymbolStart + 1);
    String result = data.substring(indexSymbolStart + 1, numberBetween_symbolStart_symbolEnd);
    Serial.println(" voici le findSelect");
    Serial.println("=============data : " + data);
    Serial.println("indexStart: " + (String)indexStart);
    Serial.println("indexAfterStart: " + (String)indexAfterStart);
    Serial.println("indexSymbolStart: " + (String)indexSymbolStart);
    Serial.println("numberBetween_symbolStart_symbolEnd: " + (String)numberBetween_symbolStart_symbolEnd);
    Serial.println("résultat : " + result);
    return result;
}

void step_catm1_function()
{
    switch (currentStepCATM1)
    {
    case CATM1_POWER_ON:
        Serial.println("[CATM1_POWER_ON]");
        Send_AT("AT+CNMP=38");
        Send_AT("AT+CMNB=1");

        Send_AT("AT+CNACT=0,0");
        currentStepCATM1 = CATM1_CGDCONT;

        break;

    case CATM1_CGDCONT:
        if (machineCATM1.updateATState(taskCATM1_CGDCONT))
        {
            Send_AT("AT+CGNAPN");
            Send_AT("AT+CNCFG=0,1,iot.1nce.net");
            currentStepCATM1 = CATM1_INFO;
        }
        break;

    case CATM1_INFO:
        Serial.println("[CATM1_INFO]");
        if (machineCATM1.updateATState(taskCATM1_CEREG))
        {
            String resultPDP = findSelect(Send_AT("AT+CNACT=0,1", 15000), "PDP", 4, ",", " ");
            if (resultPDP == "ACTIVE")
            {
                Serial.print("ACTIVE detecté");
            }

            // informations for you on CAT-M1 connexion
            Send_AT("AT+CGATT?");
            Send_AT("AT+CNACT?", 3000);
            String resultCNACT = findSelect(Send_AT("AT+CNACT?", 3000), "+CNACT:", 12, "\"", ".");
            if (resultCNACT == "10")
            {
                Serial.println("10 detecté");
            }
            Send_AT("AT+GSN");
            Send_AT("AT+CCID");
            Send_AT("AT+COPS?");
            Send_AT("AT+CEREG?");
            // signal quality
            Send_AT("AT+CSQ");
            currentStepCATM1 = CATM1_DONE;
        }
        break;

    case CATM1_POWER_OFF:
        Serial.println("[CATM1_POWER_OFF]");
        // Exemple : désactivation du module, libération des ressources, etc.
        // Si tout est OK, passer à l'étape suivante :
        currentStepCATM1 = CATM1_DONE;
        break;

    case CATM1_DONE:
        Serial.println("[CATM1_DONE]");
        currentStep4G = STEP_SEND_CBOR;
        // Fin du process CAT-M1, prêt pour une nouvelle séquence ou attente

        break;
    }
}
