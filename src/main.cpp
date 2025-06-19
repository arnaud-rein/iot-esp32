#include <Arduino.h>
#include "SIM7080G_POWER.hpp"
#include "SIM7080G_SERIAL.hpp"
#include "SIM7080G_CATM1.hpp"
#include "machineEtat.hpp"
#include "pipeline.hpp"
#include "GnssUtils.hpp"
#include <EEPROM.h>
#include "PIPELINE_GLOBAL.hpp"
// #include "ROM.hpp"
#include "receiveCBOR.hpp"
#include "RECEIVE.hpp"
#include "GLOBALS.hpp"

#define EEPROM_SIZE 256

String getIMEI(const String &rawResponse)
{
  Serial.println("🔍 Réponse AT brute reçue :");
  Serial.println("[" + rawResponse + "]");

  // On coupe la réponse en lignes
  int start = 0;
  int end = rawResponse.indexOf('\n');
  while (end != -1)
  {
    String line = rawResponse.substring(start, end);
    line.trim(); // Supprime les \r, \n, espaces

    // L'IMEI est normalement une ligne de 15 chiffres
    if (line.length() == 15 && line.toInt() != 0)
    {
      Serial.println("✅ IMEI détecté : " + line);
      return line;
    }

    start = end + 1;
    end = rawResponse.indexOf('\n', start);
  }

  Serial.println("⚠️ Aucune ligne contenant un IMEI trouvée.");
  return "";
}

void everyX()
{
  if ((millis() - periodEveryX) > 500)
  {
    Serial.print("[");
    // Serial.println("100000ms");
    pipelineGlobal();
    periodEveryX = millis();
  }
}

void setup()
{
  pinMode(PIN_PWRKEY, OUTPUT);
  Serial.begin(115200); // init port uart // on a aussi un port uart qui pointe vers notre pc
  reboot_SIM7080G();
  Serial.println("Around the World"); // CTRL + ALT + S

  String gsnRaw = Send_AT("AT+GSN");
  imei = getIMEI(gsnRaw);
  period10min = millis();
  periodEveryX = millis();
}

void loop()
{
  // put your main code here, to run repeatedly:
  everyX();
}
