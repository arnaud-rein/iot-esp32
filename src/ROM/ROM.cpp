#include "ROM.hpp"
// 🔹 Fonction pour écrire un uint32_t manuellement
void writeUInt32(int addr, uint32_t val) {
  for (int i = 0; i < 4; i++) {
    EEPROM.write(addr + i, (val >> (8 * (3 - i))) & 0xFF);
  }
}

// 🔹 Fonction pour lire un uint32_t
uint32_t readUInt32(int addr) {
  uint32_t val = 0;
  for (int i = 0; i < 4; i++) {
    val |= EEPROM.read(addr + i) << (8 * (3 - i));
  }
  return val;
}

// 🔹 Stockage d’un Float_gnss
void writeFloatGnss(int addr, const Float_gnss& f) {
  EEPROM.write(addr, f.ent);
  writeUInt32(addr + 1, f.dec);
}

// 🔹 Lecture d’un Float_gnss
Float_gnss readFloatGnss(int addr) {
  Float_gnss f;
  f.ent = EEPROM.read(addr);
  f.dec = readUInt32(addr + 1);
  return f;
}

// 🔹 Écriture d’une String à taille fixe (tronquée si trop longue)
void writeFixedString(int addr, const String& str, int maxLength) {
  for (int i = 0; i < maxLength; i++) {
    if (i < str.length()) {
      EEPROM.write(addr + i, str[i]);
    } else {
      EEPROM.write(addr + i, 0);  // padding avec \0
    }
  }
}

// 🔹 Lecture d’une String à taille fixe
String readFixedString(int addr, int maxLength) {
  char buf[maxLength + 1];
  for (int i = 0; i < maxLength; i++) {
    buf[i] = EEPROM.read(addr + i);
  }
  buf[maxLength] = '\0';
  return String(buf);
}

void afficherCoordonneesDepuisEEPROM(bool* afficher) {
    if (!afficher || !(*afficher)) {
        return;
    }

    EEPROM.begin(EEPROM_SIZE);

    Float_gnss lat = readFloatGnss(ADDR_LATITUDE);
    Float_gnss lng = readFloatGnss(ADDR_LONGITUDE);
    String ts = readFixedString(ADDR_TIMESTAMP, 20);

    Serial.println("------ Coordonnées EEPROM ------");
    Serial.print("Latitude : ");
    Serial.print(lat.ent); Serial.print("."); Serial.println(lat.dec);

    Serial.print("Longitude : ");
    Serial.print(lng.ent); Serial.print("."); Serial.println(lng.dec);

    Serial.print("Horodatage : ");
    Serial.println(ts);
}
