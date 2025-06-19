#ifndef ARGALI_PINOUT_HPP
#define ARGALI_PINOUT_HPP

// Définition des constantes
#define PIN_PWRKEY 7
#define Sim7080G Serial1
#define Sim7080G_BAUDRATE 57600
#define PINGGY_LINK "rnzcn-92-184-121-52.a.free.pinggy.link"
#define PINGGY_PORT 40327
#define MAX_COORDS 10
#include <Arduino.h>
#include <vector>
// #include "GNSS/SIM7080G_GNSS.hpp"

struct MessageCoord
{
    String data;
    bool endCBOR = true; // true = prêt à envoyer, false = en cours de traitement
};

extern MessageCoord listeCoordonnees[MAX_COORDS];
extern int nbCoordonnees;
extern String tableauJSONString;
extern String imei;

// extern std::vector<MessageCoord> listeCoordonnees;

extern unsigned long PERIODE_CBOR; // déclaration "extern"
extern unsigned long periodEveryX;
extern unsigned long period10min;
extern unsigned long periodGNSS;

extern bool oneRun;

#endif // ARGALI_PINOUT_HPP
