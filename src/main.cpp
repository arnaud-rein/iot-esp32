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

  period10min = millis();
  period100000 = millis();
}

void loop()
{
  // put your main code here, to run repeatedly:
  everyX();
}
