// Définition des constantes
#define PIN_PWRKEY 7
#define Sim7080G Serial1
#define Sim7080G_BAUDRATE 57600
#define PINGGY_LINK "rngvr-92-184-123-230.a.free.pinggy.link"
#define PINGGY_PORT 43967
// #define PERIODE_CBOR 1UL


extern unsigned long PERIODE_CBOR;  // déclaration "extern"
extern unsigned long periodB; 

extern  bool END_CBOR_SEND;  // déclaration "extern"
extern  bool STEP_4G_TEST;  // déclaration "extern"
extern bool premierTour; 
extern bool oneRun; 
