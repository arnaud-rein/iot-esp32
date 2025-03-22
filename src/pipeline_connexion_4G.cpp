#include "./CBOR/pipeline.hpp"
// -----------Utilisation Machine d'état ----------------------->
// SECTION BIENTOT REFACTOR DANS UN DOSSIER CAR IL Y A UN BUG QUANND ON DEPLACE CE CODE 
MachineEtat machine;
ATCommandTask taskSim("AT+SIMCOMATI", "860016044667504", 10, 3000);
ATCommandTask taskCNACT("AT+CNACT=0,1", "PDP", 15, 5000);
boolean test = true;
ProcessStep currentStep = STEP_INIT;

// Création de deux tâches AT indépendantes
ATCommandTask task1("AT+CAOPEN=0,0,\"TCP\",\"rnwaa-2a01-cb0d-8049-29ce-a8bf-83af-ebdc-1b69.a.free.pinggy.link\",35555", "OK", 15, 15000);
// ATCommandTask task2("AT+COPS?", "+COPS:", 3, 3000);
unsigned long period1;
void switchPipeline(){ //#machineEtat //http://127.0.0.1:5500/documentation/index.html#machineEtat

  period1 = millis();

    switch (currentStep) {
        case STEP_INIT:
            Serial.println("[STEP_INIT] Démarrage...");
            currentStep = STEP_WAIT_SIM;
            break;

        case STEP_WAIT_SIM:
            Serial.println("[STEP_WAIT_SIM] Attente de la fin de taskSim...");
            if(millis() - period1 > 3000){
                if (!taskSim.isFinished ) {
                    machine.updateATState(taskSim);
                    period1 = millis();
                } else {
                    currentStep = STEP_CONFIG_CATM1;
                    period1 = millis();
                }
                
            }
            break;

        case STEP_CONFIG_CATM1:
            Serial.println("[STEP_CONFIG_CATM1] Configuration du CATM1...");
            if (millis() - period1 > 3000) {
                // Éteindre le GNSS avant d'activer CATM1
                // gnssTurnOff();
                Send_AT("AT+CNMP=38");
                Send_AT("AT+CMNB=1");
                Send_AT("AT+CNACT=0,0");
                Send_AT("AT+CGDCONT=1,\"IP\",\"iot.1nce.net\"");
                Send_AT("AT+CGNAPN");
                Send_AT("AT+CNCFG=0,1,iot.1nce.net");
                Send_AT("AT+CEREG?");
               
            
            currentStep = STEP_WAIT_CNACT;
            }
            break;

        case STEP_WAIT_CNACT:
            Serial.println("[STEP_WAIT_CNACT] Attente de la fin de taskCNACT...");
            if (millis() - period1 > 3000) {
                if (!taskCNACT.isFinished) {
                    machine.updateATState(taskCNACT);
                } else {
                    currentStep = STEP_DONE;
                }
                break;
            }

        case STEP_DONE:
        if (millis() - period1 > 3000) {
            Serial.println("[STEP_DONE] Processus terminé !");
        }
            // Si tu veux recommencer depuis le début après la fin :
            // currentStep = STEP_INIT;
            break;
    }
}
