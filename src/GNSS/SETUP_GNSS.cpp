#include "SETUP_GNSS.hpp"


void initGnssCongif(){
    // Serial.println("GNSS"); 
    // Serial.println(gnssTurnOn());
    // Serial.println(check_GNSS_Status());
    // Serial.println(get_GNSS_Mode());

    Serial.println("\n[GNSS INIT]");

  // Allume le GNSS
  Serial.println("------------------INIT de GGNSPWR----------------->");
  Send_AT("AT+CGNSPWR=1", 1000);
  Serial.println("------------------END INIT de GGNSPWR----------------->");

  // Optionnel : désactiver la sortie automatique NMEA
  Send_AT("AT+CGNSTST=0", 500);

  // Lecture de l’état GNSS
  String response = Send_AT("AT+CGNSINF", 1000);
  Serial.println("\nRéponse CGNSINF initiale :");
  Serial.println(response);
}