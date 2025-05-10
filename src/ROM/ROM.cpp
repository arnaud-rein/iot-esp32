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

// Float_gnss readFloatGnss(int addr, boolean lat) {
//   Float_gnss f;
//   if(lat){
//     f.ent = EEPROM.read(addr);
//     f.dec = readUInt32(addr + 3);
//     return f;
//   }else{
//     f.ent = EEPROM.read(addr);
//     f.dec = readUInt32(addr + 2);
//     return f;
//   }
// }

// 🔹 Écriture d’une String à taille fixe (tronquée si trop longue)
void writeFixedString(int addr, const String& str, int maxLength) {
  Serial.println("dans writeFixedString");
  Serial.println("String str : " + str);
  Serial.println("addr : " + String(addr) + "longeur de la chaîn maxLength : " + String(maxLength) + " str.length : " + str.length());

  for (int i = 0; i < maxLength; i++) {
    Serial.print("------------------> BOUCLE FOR : ");
    
      Serial.println(str[i]);
    
  }
  for (int i = 0; i < maxLength; i++) {
    Serial.println("++++++++++++ BOUCLE FOR");
    if (i < str.length()) {
      EEPROM.write(addr + i, str[i]);
      Serial.print("EEPROM.write: ");
      Serial.println(str[i]);
    } else {
      EEPROM.write(addr + i, 0);  // padding avec \0
    }
  }

  for (int i = 0; i < maxLength; i++) {
    char c = EEPROM.read(addr + i);
    Serial.print("Byte ");
    Serial.print(i);
    Serial.print(" : ");
    Serial.println((int)c); // Affiche la valeur numérique
  }
}

// // 🔹 Lecture d’une String à taille fixe
// String readFixedString(int addr, int maxLength) {
//   char buf[maxLength + 1];
//   for (int i = 0; i < maxLength; i++) {
//     buf[i] = EEPROM.read(addr + i);
//   }
//   buf[maxLength] = '\0';
//   return String(buf);
// }
String readFixedString(int addr, int maxLength) {
  char buf[maxLength + 1];
  // Serial.println("---------dans readFixedString ############");
  for (int i = 0; i < maxLength; i++) {
    char c = EEPROM.read(addr + i);
    // Remplace les caractères non imprimables par un point
    buf[i] = (c >= 1 && c <= 150) ? c : '.';
  }
  buf[maxLength] = '\0';
  return String(buf);
}

void writeSimIdToEEPROM(const String& simId) {
  Serial.println("simdId String : " + simId + " longeur de la chaîne : " + String(simId.length()));
  if (simId.length() > 30) {
    Serial.println("[Chaîne trop longue]");
    return;
  }
  writeFixedString(100, simId, 15);
  EEPROM.commit(); // Ne pas oublier pour persister dans la flash
}

String readSimIdFromEEPROM() {
  return readFixedString(ADDR_SIM_ID, 10);
}

String getEsp32Id() {
  uint64_t chipid = ESP.getEfuseMac();
  char idBuffer[13]; // 12 caractères hex + '\0'
  sprintf(idBuffer, "%04X%08X", (uint16_t)(chipid >> 32), (uint32_t)chipid);
  return String(idBuffer);
}

void writeEspIdToEEPROM() {
  String id = getEsp32Id();
  writeFixedString(ADDR_SIM_ID, id, 10); // 10 caractères max
  EEPROM.commit(); // Important pour enregistrer
}

void writeEspIdIfNotSet() {
  if (readFixedString(ADDR_SIM_ID, 10).length() == 0) {
    writeEspIdToEEPROM();
  }
}

// String readEspIdFromEEPROM() {
//   return readFixedString(ADDR_SIM_ID, 10);
// }

String readEspIdFromEEPROM() {
  String id = readFixedString(ADDR_SIM_ID, 10);
  if (id.length() == 0 || id.indexOf('.') != -1) {
    return "UNKNOWN";
  }
  return id;
}

void resetSimIdEEPROM() {
  for (int i = 0; i < 10; i++) {
    EEPROM.write(ADDR_SIM_ID + i, 0);
  }
  EEPROM.commit();
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


String getCoordonneesDepuisEEPROM() {
  // EEPROM.begin(EEPROM_SIZE);

  String simId = readSimIdFromEEPROM();
  Float_gnss lat = readFloatGnss(ADDR_LATITUDE);
  Float_gnss lng = readFloatGnss(ADDR_LONGITUDE);
  String imei = readFixedString(100, 15);
  // Serial.println("---------voici le message SIM ID =================================");
  // Serial.println(simId);
  // Serial.println("------------------------------------------------> result < -------------------------");
  // // String ts = readFixedString(ADDR_TIMESTAMP, 20);
  // String simId = readEspIdFromEEPROM();

  // Formatage avec précision
  String latitude = String(lat.ent) + "." + String(lat.dec);
  String longitude = String(lng.ent) + "." + String(lng.dec);
 
  // String result = "{name:'test', position{Latitude: " + latitude + ", Longitude: " + longitude + "}}";
  // String result = "{\"name\":\"test\",\"position\":{\"latitude\":" + latitude + ",\"longitude\":" + longitude + "}}";
  String result = "{\"name\":\"" + imei + "\",\"position\":{\"latitude\":" + latitude + ",\"longitude\":" + longitude + "}}";
  // Serial.println(result);

  // Serial.println("result qui va être convert en CBOR Latitude: " + result);
  return result;
}
