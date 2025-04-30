#ifndef SIM7080G_GNSS_HPP
#define SIM7080G_GNSS_HPP


#include <Arduino.h> 
#include "ARGALI_PINOUT.hpp"
#include "SIM7080G_SERIAL.hpp"

String gnssTurnOn();
String gnssTurnOff();
String check_GNSS_Status() ;

String get_GNSS_Info(); 
String get_GNSS_Mode();
String getValueOfGnssData(String gnssData, int16_t choiceValue);
String getTimeStamp(String gnssData);
String getRunStatus(String gnssData);
String getAltitude(String gnssData);
String getLng(String gnssData);
String getLat(String gnssData);
String getTimeStamp(String gnssData);
String getFixStatus(String gnssData);
String getLatLng(String gnssData);




struct Float_gnss{
    uint8_t ent; 
    uint32_t dec;
};

struct Coord{
    Float_gnss latitude; 
    Float_gnss longitude; 
};


struct Gnss{
    String runStatus;
    String fixStatus;
    String timeStamp; 
    Coord coordonnees; 
    String altitude;
};

Coord parserLatLng(String lat, String lng);
Float_gnss parseGNSS(String coord);
Gnss getGnssResponse();

#endif // SIM7080G_GNSS_HPP