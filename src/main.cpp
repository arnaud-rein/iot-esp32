#include <Arduino.h>
#include  "SIM7080G_POWER.hpp"
#include "SIM7080G_SERIAL.hpp"
// #include "SIM7080G_CATM1.hpp"
#include "machineEtat.hpp"
// #include "pipeline.hpp"
#include "./CBOR/pipeline.hpp"
#include "./GNSS/SETUP_GNSS.hpp"
#include "./GNSS/DisplayLatLng.hpp"
#include <EEPROM.h>
#include "PIPELINE_GLOBAL.hpp"
// #include "./SEND/pipeline.hpp"

#define EEPROM_SIZE 256  // 
// ATCommandTask gnssPowerOn("AT+CGNSPWR=1", "OK", 3, 2000); // Commande d’activation GNSS

// MachineEtat machine2; // Instance de la machine d’état
// bool afficherDepuisMemoire = true;
// bool* ptrAfficherMemoire = &afficherDepuisMemoire;
bool oneRun = true; 


unsigned long periodA; 
unsigned long periodB; 


// 🔹 Fonction pour écrire une String
void writeStringToEEPROM(int addrOffset, const String &str) {
  int len = str.length();
  if (len + 1 + addrOffset > EEPROM_SIZE) {
    Serial.println("Erreur : chaîne trop longue pour l'EEPROM !");
    return;
  }

  EEPROM.write(addrOffset, len); // on écrit la longueur d'abord
  for (int i = 0; i < len; i++) {
    EEPROM.write(addrOffset + 1 + i, str[i]); // caractères un par un
  }
  EEPROM.commit(); // Sauvegarde dans la flash
}

// 🔹 Fonction pour lire une String
String readStringFromEEPROM(int addrOffset) {
  int len = EEPROM.read(addrOffset); // on lit la longueur
  if (len <= 0 || len > EEPROM_SIZE - addrOffset - 1) {
    return "[Lecture invalide]";
  }

  char data[len + 1]; // +1 pour le caractère de fin '\0'
  for (int i = 0; i < len; i++) {
    data[i] = EEPROM.read(addrOffset + 1 + i);
  }
  data[len] = '\0';
  return String(data);
}


void everyX(){
  // sendMessageCBOR("Test du refactor");
  // sendMessageCBOR("DEUXIEME TACHE");
  // sendMessageCBOR("test");
  // Serial.println("dans le every");
  if((millis() - periodA) > 3000){
    if(oneRun){

      pipelineSwitchGlobal();
    }
   
    periodA = millis(); 
  }
  if(STEP_4G_TEST){
    if(oneRun){
      setup_CATM1();
      oneRun = false; 
    }
    
    if(!oneRun){
      // Serial.println("++++++++++++++++++++++++++++++++++++++++++++DANS STEP_SEND_4G++++++++++++++++++++++++++++++++++++++");
      // sendMessageCBOR(getCoordonneesDepuisEEPROM().c_str());
      
      if((millis() - periodB) > 3000){
        Serial.println("--");
        Serial.println("--");
        Serial.println("");
        Serial.print("[");
        Serial.print(millis());
        Serial.print("ms]" );
        Serial.println("");
        Serial.println("--");
        Serial.println("--");
        periodB = millis();
        // Serial.print("PWR?   ==>   "); 
                        // Send_AT("AT+CGNSPWR=0");
                        // Serial.print(Send_AT("AT+CGNSPWR?"));
      }
        // sendMessageCBOR(getCoordonneesDepuisEEPROM().c_str());
        
        sendMessageCBOR("{\"name\":\"Evian\",\"position\":{\"latitude\":666.85,\"longitude\":3.35}}");
    }
  }
}

void setup() {
  pinMode(PIN_PWRKEY, OUTPUT);
  // turn_on_SIM7080G();
  Serial.begin(115200); // init port uart // on a aussi un port uart qui pointe vers notre pc
  reboot_SIM7080G();
  Serial.println("Around the World"); // CTRL + ALT + S
  // setup_CATM1();
  periodA = millis();
  periodB = millis(); 
}

void loop() {
  // put your main code here, to run repeatedly:
  everyX();
}

