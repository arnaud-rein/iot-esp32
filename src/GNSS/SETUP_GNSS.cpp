#include "SETUP_GNSS.hpp"


void initGnssCongif(){
    Serial.println("GNSS"); 
    Serial.println(gnssTurnOn());
    Serial.println(check_GNSS_Status());
    Serial.println(get_GNSS_Mode());
}