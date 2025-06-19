#ifndef ROM
#define ROM

#include <Arduino.h>
#include <EEPROM.h>
#include "SIM7080G_GNSS.hpp"

// Taille de l'EEPROM utilisée
#define EEPROM_SIZE 256

// Adresses fixes pour les données
#define ADDR_SIM_ID 0
#define ADDR_LATITUDE 10
#define ADDR_LONGITUDE 20
#define ADDR_TIMESTAMP 30

// 🔹 Fonction pour écrire un uint32_t en EEPROM
void writeUInt32(int addr, uint32_t val);

// 🔹 Fonction pour lire un uint32_t depuis l'EEPROM
uint32_t readUInt32(int addr);

// 🔹 Écriture d’un Float_gnss dans l'EEPROM
void writeFloatGnss(int addr, const Float_gnss &f);

// 🔹 Lecture d’un Float_gnss depuis l'EEPROM
// Float_gnss readFloatGnss(int addr);
Float_gnss readFloatGnss(int addr, boolean lat);

// 🔹 Écriture d’une String à taille fixe
void writeFixedString(int addr, const String &str, int maxLength);

// 🔹 Lecture d’une String à taille fixe
String readFixedString(int addr, int maxLength);

void afficherCoordonneesDepuisEEPROM(bool *afficher);

String getCoordonneesDepuisEEPROM();

void writeIMEI();

void writeEspIdIfNotSet();

void resetSimIdEEPROM();

String parseGSNResponse(const String &rawResponse);

void writeSimIdToEEPROM(const String &simId);

String readSimIdFromEEPROM();

#endif // EEPROM_GNSS_HPP
