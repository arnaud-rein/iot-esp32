#include "ARGALI_PINOUT.hpp"

unsigned long PERIODE_CBOR = 123UL; // définition et initialisation
unsigned long periodB = 123UL;      // définition et initialisation
unsigned long period100000 = 123UL; // définition et initialisation
unsigned long period10min = 123UL;  // définition et initialisation
unsigned long periodA = 123UL;      // définition et initialisation
unsigned long periodGNSS = 123UL;   // définition et initialisation
bool END_CBOR_SEND = false;
bool premierTour = true;
bool oneRun = true;
std::vector<MessageCoord> listeCoordonnees;