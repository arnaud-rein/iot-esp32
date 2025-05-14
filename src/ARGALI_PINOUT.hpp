#ifndef ARGALI_PINOUT_HPP
#define ARGALI_PINOUT_HPP

// Définition des constantes
#define PIN_PWRKEY 7
#define Sim7080G Serial1
#define Sim7080G_BAUDRATE 57600
#define PINGGY_LINK "rnhcn-92-184-121-62.a.free.pinggy.link"
#define PINGGY_PORT 44487
#include <Arduino.h>
#include <vector>

struct MessageCoord
{
    String data;
    bool endCBOR = true; // true = prêt à envoyer, false = en cours de traitement
};

extern std::vector<MessageCoord> listeCoordonnees;

extern unsigned long PERIODE_CBOR; // déclaration "extern"
extern unsigned long periodB;
extern unsigned long period100000;
extern unsigned long period10min;
extern unsigned long periodA;
extern unsigned long periodGNSS;

extern bool END_CBOR_SEND; // déclaration "extern"
extern bool premierTour;
extern bool oneRun;

#endif // ARGALI_PINOUT_HPP
