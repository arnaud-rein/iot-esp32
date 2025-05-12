#include "EVERY.hpp"


void restartPipeline(){

    if((millis() - period10min) > 10000){
        // Serial.println(getCoordonneesDepuisEEPROM());
        periodGNSS = millis();
        premierTour = true; 
        oneRun = true;
        currentStepGLOBAL = STEP_INIT_GLOBAL; 
        afficherDepuisMemoire = false;
        endCBOR = true; 
        Send_AT("AT+CGNSPWR=1");
        currentStepCBOR = STEP_INIT_CBOR;
        taskCBOR_CASEND = nullptr;
        currentTaskCBOR = nullptr;
        command = "";
        resetCommandOPEN_CONNEXION = true; 
        resetCommandCEREG = true; 
        resetCommandCLOSE_CONNEXION = true; 
    
        // DEFINITION DES VARIABLES INDISPENSABLE AU BON FONCTIONNEMENT DE CETTE PIPELINE
      cborDataPipeline.clear();
        period10min = millis(); 
      }
    
      if(premierTour){
        coordPipeline();
        period10min = millis();
      }


}


void coordPipeline(){
  if((millis() - periodA) > 1000){
    if(oneRun){
      // Serial.println("dans coordPipeline    ===    ---");
      pipelineSwitchGlobal();
    }
    
    periodA = millis(); 
  }
  if(!oneRun){
    pipelineSwitchGlobal();
  }
  
}

