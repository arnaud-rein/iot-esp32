#include "DisplayTimeStamp.hpp"


void displayTimeStamp(){
        // Affichage des valeurs
        String gnssData =  get_GNSS_Info();

        tm timeStruct = parserTimeStamp(getTimeStamp(gnssData));
        Serial.println("📅 Timestamp stocké dans struct tm :");
        Serial.printf("Date : %04d-%02d-%02d\n", timeStruct.tm_year + 1900, timeStruct.tm_mon + 1, timeStruct.tm_mday);
        Serial.printf("Heure : %02d:%02d:%02d\n", timeStruct.tm_hour, timeStruct.tm_min, timeStruct.tm_sec);
}