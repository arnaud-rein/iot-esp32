// Définition des constantes
#define PIN_PWRKEY 7
#define Sim7080G Serial1
#define Sim7080G_BAUDRATE 57600
#define PINGGY_LINK "rnfye-92-184-121-26.a.free.pinggy.link"
#define PINGGY_PORT 44251
// #define PERIODE_CBOR 1UL


extern unsigned long PERIODE_CBOR;  // déclaration "extern"
extern  bool END_CBOR_SEND;  // déclaration "extern"
extern  bool STEP_4G_TEST;  // déclaration "extern"
extern bool premierTour; 
