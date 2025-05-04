#include "PIPELINE_GLOBAL.hpp"


PipelineGLOBAL currentStepGLOBAL = STEP_INIT_GLOBAL; 
ATCommandTask gnssPowerOn("AT+CGNSPWR=1", "OK", 3, 2000); // Commande d’activation GNSS
ATCommandTask gnssPowerOff("AT+CGNSPWR=0", "OK", 3, 2000); // Commande d’activation GNSS
MachineEtat machine2; // Instance de la machine d’état
bool afficherDepuisMemoire = false;
// bool oneRun = true; 

//PIPELINE 
void pipelineSwitchGlobal(){

    
    switch(currentStepGLOBAL){

        case STEP_INIT_GLOBAL:
            // STEP_INIT_CBOR_FUNCTION();
            Serial.println("Lancement Pipelie GLOBAL");
            Serial.println("-------------------------------->");
            Serial.println("------------------------------->");
            currentStepGLOBAL = STEP_GNSS; 
            break;

        case STEP_GNSS:
        if (!gnssPowerOn.isFinished) {
            Serial.println("----------------gnssPowerOn------------->");
            machine2.updateATState(gnssPowerOn);
            // Send_AT("AT+CGNSMOD=1,1,1,1,1", 500);
            // Serial.println(Send_AT("ATI", 500));
            // Send_AT("AT+CGNSTST=1", 500);  // Active la sortie NMEA sur le port série
            
          } else {
            
            // Serial.println("[INFO] GNSS activé ou erreur atteinte.");
            Serial.println("-----------------GNSSINF--------------"); 
            Send_AT("AT+CGNSTST=1", 500);
            Serial.println(Send_AT("AT+CGNSMOD?"));
            // Serial.println(Send_AT("AT+CGNSTST?"));
            Serial.println(Send_AT("AT+CGNSPWR?", 500));      // Vérifie état GNSS
            String response = Send_AT("AT+CGNSINF", 2000);
            Serial.println(response);
            if(!afficherDepuisMemoire){
                DisplayLatLngInfo(&afficherDepuisMemoire);
            }else{
                machine2.updateATState(gnssPowerOff);
                if(!gnssPowerOff.isFinished){
                    currentStepGLOBAL = STEP_END_GLOBAL;
                    END_CBOR_SEND = false; 
                    Serial.println("end cbor send" + String(END_CBOR_SEND));
                    Send_AT("AT+CGNSPWR=0");
                    Send_AT("AT+CGNSPWR=0");
                    STEP_4G_TEST = true; 
                }
            }
          }
            break;

        // case STEP_SEND_4G:
        //     if(oneRun){
        //         setup_CATM1();
        //         oneRun = false; 
        //     }else{
        //         Serial.println("++++++++++++++++++++++++++++++++++++++++++++DANS STEP_SEND_4G++++++++++++++++++++++++++++++++++++++");
                // sendMessageCBOR(getCoordonneesDepuisEEPROM().c_str());
        //         sendMessageCBOR("test");
        //     }
            
        //     if(END_CBOR_SEND){

        //         currentStepGLOBAL = STEP_END_GLOBAL; 
        //     }
        //     break;
        
        case STEP_END_GLOBAL:
            // Serial.println("END----------------->");
            // Serial.println("END---------------->");
            // Serial.println("END--------------->");
            Serial.println("|");
            Serial.println("|");
            Serial.println("|");
            break;

    }
}