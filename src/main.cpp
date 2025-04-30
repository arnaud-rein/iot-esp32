#include <Arduino.h>
#include  "SIM7080G_POWER.hpp"
#include "SIM7080G_SERIAL.hpp"
#include "SIM7080G_CATM1.hpp"
#include "machineEtat.hpp"
// #include "pipeline.hpp"
#include "./CBOR/pipeline.hpp"
#include "./GNSS/SETUP_GNSS.hpp"
#include "./GNSS/DisplayLatLng.hpp"
#include <EEPROM.h>

#define EEPROM_SIZE 64  // 


unsigned long periodA; 


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
  if((millis() - periodA) > 3000){
    // DisplayLatLngInfo();
    periodA = millis(); 
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
  // initGnssCongif();
  if (!EEPROM.begin(EEPROM_SIZE)) {
    Serial.println("Erreur d'initialisation de l'EEPROM !");
    return;
  }

  Serial.print("Taille EEPROM définie : ");
  Serial.println(EEPROM_SIZE);
  Serial.println("Contenu de l'EEPROM :");

  // Affiche chaque octet
  for (int i = 0; i < EEPROM_SIZE; i++) {
    byte value = EEPROM.read(i);
    Serial.print("Adresse ");
    Serial.print(i);
    Serial.print(" : ");
    Serial.println(value);
  }

    // Exemple : écrire la valeur 42 à l'adresse 0
    // EEPROM.write(0, 42);

    // Très important : commit pour sauvegarder dans la flash (ROM)
    // EEPROM.commit();
  
    // Lire ce qu'on vient d'écrire
    int val = EEPROM.read(0);
    Serial.print("Valeur lue en adresse 0 : ");
    Serial.println(val);

      // 🔸 Écrire "bonjour" en EEPROM à partir de l'adresse 0
  writeStringToEEPROM(0, "bonjour");

  // 🔸 Lire ce qui a été écrit
  String mot = readStringFromEEPROM(0);
  Serial.print("Mot lu dans l'EEPROM : ");
  Serial.println(mot);
}

void loop() {
  // put your main code here, to run repeatedly:
  everyX();
}

