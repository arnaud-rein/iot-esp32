#include <Arduino.h>
#include "SIM7080G_POWER.hpp"
#include "SIM7080G_SERIAL.hpp"
#include "SIM7080G_CATM1.hpp"
#include "machineEtat.hpp"
#include "./CBOR/pipeline.hpp"
#include "./GNSS/SETUP_GNSS.hpp"
#include "./GNSS/DisplayLatLng.hpp"
#include <EEPROM.h>
// #include "PIPELINE_GLOBAL.hpp"
#include "./ROM/ROM.hpp"
#include "./RECEIVE_FROM_SERVEUR_TCP/receiveCBOR.hpp"
#include "./RECEIVE_FROM_SERVEUR_TCP/RECEIVE.hpp"
#include "./EVERY/EVERY.hpp"

#define EEPROM_SIZE 256

// Setup du vecteur
std::vector<String> messages;

void everyX()
{
  if ((millis() - period100000) > 500)
  {
    Serial.print("[");
    // Serial.println("100000ms");
    pipelineGlobal();
    period100000 = millis();
  }
}

void setup()
{
  pinMode(PIN_PWRKEY, OUTPUT);
  Serial.begin(115200); // init port uart // on a aussi un port uart qui pointe vers notre pc
  reboot_SIM7080G();
  Serial.println("Around the World"); // CTRL + ALT + S

  periodA = millis();
  periodB = millis();
  period10min = millis();
  period100000 = millis();

  // // Un long JSON
  // String json1 = R"rawliteral({
  //   "name": "Arnaud",
  //   "position": {
  //       "latitude": 48.8566,
  //       "longitude": 2.3522
  //   },
  //   "timestamp": "2025-05-13T19:05:00Z"
  // })rawliteral";

  // String json2 = R"rawliteral({
  //   "name": "Lisa",
  //   "position": {
  //       "latitude": 47.2184,
  //       "longitude": -1.5536
  //   },
  //   "timestamp": "2025-05-13T19:10:00Z"
  // })rawliteral";

  // // Ajout dans le vector
  // messages.push_back(json1);
  // messages.push_back(json2);

  // // Affichage des JSON dans le terminal série
  // Serial.println("=== JSON messages ===");
  // for (const String &msg : messages)
  // {
  //   Serial.println(msg);
  //   Serial.println(); // Ligne vide entre les messages
  // }
}

void loop()
{
  // put your main code here, to run repeatedly:
  everyX();
}
