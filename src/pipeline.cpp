#include "pipeline.hpp"


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





void sendMinimalCBORMessage() { // http://127.0.0.1:5500/documentation/index.html#pinggy
  // 1. Préparer un message simple
  const char* message = "coucou serveur";
  json j = message;

  // 2. Convertir en CBOR
  std::vector<uint8_t> cborData = json::to_cbor(j);

  // 3. Ouvrir la connexion TCP (Pinggy)
  Send_AT("AT+CAOPEN=0,0,\"TCP\", " + (String) PINGGY_LINK + ", " + (String) PINGGY_PORT + "");
  delay(3000);  // attendre que la connexion soit établie

  // 4. Informer le module qu’on va envoyer N octets
  String cmd = "AT+CASEND=0," + String(cborData.size());
  Send_AT(cmd);
  delay(500);  // attendre le prompt '>'

  // 5. Envoyer les octets CBOR
  for (uint8_t byte : cborData) {
    Sim7080G.write(byte);
  }

  Serial.println("[ENVOYÉ] CBOR minimal envoyé");

  // 6. Fermer la connexion proprement
  delay(2000);
  Send_AT("AT+CACLOSE=0");
}

// void sendMinimalCBORMessage() {
    // // 1. Préparer un message simple
    // const char* message = "coucou serveur";
    // json j = message;
    
    // // 2. Convertir en CBOR
    // // std::vector <uint8_t> cborData = json::to_cbor(j);
    // std::vector<uint8_t> cborData = {'H', 'E', 'L', 'L', 'O'};

    
    // // 3. Ouvrir la connexion TCP (Pinggy)
    // Send_AT("AT+CAOPEN=0,0,\"TCP\",\"rnajl-2a01-cb0d-8049-29ce-a8bf-83af-ebdc-1b69.a.free.pinggy.link\",43407");
    // // delay(3000);  // attendre que la connexion soit établie
    
    // // 4. Informer le module qu’on va envoyer N octets
    // String cmd = "AT+CASEND=0," + String(cborData.size());
    // Send_AT(cmd);
    // delay(100);  // attendre le prompt '>'
    
    // // 5. Envoyer les octets CBOR
    // Serial.print("Données CBOR envoyées: ");
    // for (uint8_t byte : cborData) {
    //     Serial.print(byte, HEX);
    //     Serial.print(" ");
    //     Sim7080G.write(byte);
    // }


    
    
    // Serial.println("[ENVOYÉ] CBOR minimal envoyé");
    
    // // 6. Fermer la connexion proprement
    // // delay(2000);
    // Send_AT("AT+CACLOSE=0");


    // 1. Texte brut à envoyer
// const char* message = "HELLO";

// // 2. Ouvrir la connexion TCP
// Send_AT("AT+CAOPEN=0,0,\"TCP\",\"rnpzl-2a01-cb0d-8049-29ce-a8bf-83af-ebdc-1b69.a.free.pinggy.link\",37781");
// // delay(3000);  // attendre que la connexion soit bien établie

// // 3. Envoyer la commande CASEND avec la taille du message
// String cmd = "AT+CASEND=0," + String(strlen(message));
// Send_AT(cmd);
// // delay(500);  // attendre le prompt '>'

// // 4. Envoyer les caractères un par un
// for (size_t i = 0; i < strlen(message); ++i) {
//     Sim7080G.write(message[i]);
// }

// // 5. Debug
// Serial.println("[ENVOYÉ] HELLO envoyé");

// // 6. Fermer la connexion
// // delay(2000);
// Send_AT("AT+CACLOSE=0");

    // }


// -----------Utilisation Machine d'état ----------------------->
PipelineCBOR currentStepCBOR = STEP_INIT_CBOR;
// unsigned long PERIODE_CBOR;
std::vector<uint8_t> cborDataPipeline;
MachineEtat machineCBOR; 
ATCommandTask taskCBOR_OPEN_CONNEXION("AT+CAOPEN=0,0,\"TCP\"," + (String) PINGGY_LINK + "," + (String) PINGGY_PORT, "OK", 15, 8000);

// Convertir la taille en String et concaténer correctement :
String command;
ATCommandTask* taskCBOR_CASEND = nullptr;
ATCommandTask taskCBOR_CLOSE("AT+CACLOSE=0", "OK", 15, 100);
ATCommandTask taskCBOR_CEREG("AT+CEREG?", "+CEREG: 0,5", 15, 100);
boolean endCBOR = true;
ATCommandTask* currentTaskCBOR = nullptr;

void repeatMachine(){
     // Mettre un garde-fou
     if (currentTaskCBOR) {
        machineCBOR.updateATState(*currentTaskCBOR);
    }
}


boolean chrono(uint16_t time){
    return ((millis() - PERIODE_CBOR) > time);
}

void pipelineSwitchCBOR(const char* dataMessage){

    
    switch(currentStepCBOR){

        case STEP_INIT_CBOR:
            STEP_INIT_CBOR_FUNCTION(dataMessage);
            break;



        case STEP_VERIFIER_CONNEXION:
            if(chrono(100)) {
                Serial.println("[STEP_VERIFIER_CONNEXION] init");
                if(!taskCBOR_CEREG.isFinished){
                    machineCBOR.updateATState(taskCBOR_CEREG); 
                    currentTaskCBOR = &taskCBOR_CEREG;
                    PERIODE_CBOR = millis();
                }else{
                    Serial.println("[STEP_VERIFIER_CONNEXION] success");
                    currentStepCBOR = STEP_OPEN_CONNEXION;
                    PERIODE_CBOR = millis();
                }

            }
            break;

        

        case STEP_OPEN_CONNEXION:
            if(chrono(100)) {
                Serial.println("[STEP_OPEN_CONNEXION] init");
                if(!taskCBOR_OPEN_CONNEXION.isFinished){
                    machineCBOR.updateATState(taskCBOR_OPEN_CONNEXION); 
                    currentTaskCBOR = &taskCBOR_OPEN_CONNEXION;
                    PERIODE_CBOR = millis();
                }else{
                    Serial.println("[STEP_OPEN_CONNEXION] success");
                    currentStepCBOR = STEP_DEFINE_BYTE;
                    PERIODE_CBOR = millis();
                }

            }
            break;
        
        case STEP_DEFINE_BYTE:
            if(chrono(1000)) {
                Serial.println("[STEP_DEFINE_BYTE] init");
                if(!taskCBOR_CASEND->isFinished){
                    machineCBOR.updateATState(*taskCBOR_CASEND); 
                    PERIODE_CBOR = millis();
                }else{
                    Serial.println("[STEP_DEFINE_BYTE] success");
                    currentStepCBOR = STEP_WRITE;
                    PERIODE_CBOR = millis();
                }

            }
            break;

        case STEP_WRITE:
             // 5. Envoyer les octets CBOR
            if(chrono(100)) {
                Serial.println("[STEP_WRITE] ");
                for (uint8_t byte : cborDataPipeline) {
                    Sim7080G.write(byte);
                }

                currentStepCBOR = STEP_CLOSE_CONNEXION;
                PERIODE_CBOR = millis();
            }
            
            break;

        case STEP_CLOSE_CONNEXION:
             
            if(chrono(100)) {
                Serial.println("[STEP_CLOSE_CONNEXION] init");
                if(!taskCBOR_CLOSE.isFinished){
                    machineCBOR.updateATState(taskCBOR_CLOSE);
                }else{
                    Serial.println("[STEP_CLOSE_CONNEXION] success");
                    currentStepCBOR = STEP_END;
                }
                
            }
            
            break;
            
        case STEP_END:
        
            if(endCBOR) {
                Serial.println("[STEP_END] ");
                Serial.println("#######################################################END CBOR############################################");
                endCBOR = false; 
            }
            
            break;

    }
}

unsigned long periodX = millis();


void sendMessageCBOR(){
    if((millis() - periodX) > 500){
        if(endCBOR){
            pipelineSwitchCBOR("TEST TEST TEST \n oui oui oui ::: \n end end end");
        }
        // sendMinimalCBORMessage();
        periodX = millis();
    }

}


// void STEP_INIT_CBOR_FUNCTION(const char* dataMessage){
//     if(chrono(100)) {
//         Serial.println("[STEP_INIT_CBOR] ");
//         const char* message = dataMessage;
//         json j = message;

//         // 2. Convertir en CBOR
//         cborDataPipeline= json::to_cbor(j);
//         Serial.println(cborDataPipeline.size());
//         // Convertir la taille en String et concaténer correctement :
//         String newCommand = String("AT+CASEND=0,") + String(cborDataPipeline.size());
//         Serial.println(newCommand); 

//         // Recréer l'objet taskCBOR_CASEND
//         if (taskCBOR_CASEND != nullptr) {
//             delete taskCBOR_CASEND;  // Si l'objet existait déjà, le supprimer pour éviter une fuite mémoire
//         }
//         taskCBOR_CASEND = new ATCommandTask(newCommand, ">", 15, 3000);

//         currentStepCBOR = STEP_VERIFIER_CONNEXION;
//         PERIODE_CBOR = millis();
//     }
// }