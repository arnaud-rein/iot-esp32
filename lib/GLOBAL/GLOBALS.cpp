#include "GLOBALS.hpp"

unsigned long PERIODE_CBOR = 123UL; // définition et initialisation
unsigned long periodEveryX = 123UL; // définition et initialisation
unsigned long period10min = 123UL;  // définition et initialisation
unsigned long periodGNSS = 123UL;   // définition et initialisation
bool oneRun = true;
// std::vector<MessageCoord> listeCoordonnees;

MessageCoord listeCoordonnees[MAX_COORDS];
// DataGNSS dataGNSS[MAX_COORDS];
int nbCoordonnees = 0;
String tableauJSONString;
String imei;