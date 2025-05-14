#ifndef ARGALI_PINOUT_HPP
#define ARGALI_PINOUT_HPP

// Définition des constantes
#define PIN_PWRKEY 7
#define Sim7080G Serial1
#define Sim7080G_BAUDRATE 57600
#define PINGGY_LINK "rnlgj-92-184-121-182.a.free.pinggy.link"
#define PINGGY_PORT 43183
#define MAX_COORDS 10
#include <Arduino.h>
#include <vector>

struct MessageCoord
{
    String data;
    bool endCBOR = true; // true = prêt à envoyer, false = en cours de traitement
};

extern MessageCoord listeCoordonnees[MAX_COORDS];
extern int nbCoordonnees;

// extern std::vector<MessageCoord> listeCoordonnees;

extern unsigned long PERIODE_CBOR; // déclaration "extern"
extern unsigned long period100000;
extern unsigned long period10min;
extern unsigned long periodGNSS;

extern bool oneRun;

#endif // ARGALI_PINOUT_HPP
