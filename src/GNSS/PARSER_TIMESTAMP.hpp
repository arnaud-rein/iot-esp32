#include <Arduino.h> 
#include "ARGALI_PINOUT.hpp"

String convertTimestampToLocalTime(String utcTimestamp, int timeOffset);


// // Structure pour stocker un timestamp
// struct tm {
//     int annee;   // Année (ex: 2024)
//     int mois;    // Mois (1-12)
//     int jour;    // Jour du mois (1-31)
//     int heure;   // Heure (0-23)
//     int minute;  // Minute (0-59)
//     int seconde; // Seconde (0-59)
// } ;

tm convertTimestampToLocalTimeTm(String utcTimestamp, int timeOffset);

tm parserTimeStamp(String utcTimestamp );