#include <Arduino.h>
#include  "SIM7080G_POWER.hpp"
#include "SIM7080G_SERIAL.hpp"
#include "SIM7080G_CATM1.hpp"
#include "machineEtat.hpp"
#include "pipeline.hpp"


unsigned long periodX;

void everyX(){
  if((millis() - periodX) > 6000){
    // pipelineSwitchCBOR();
    sendMinimalCBORMessage();
    periodX = millis();
  }
}

void setup() {
  pinMode(PIN_PWRKEY, OUTPUT);
  // turn_on_SIM7080G();
  Serial.begin(115200); // init port uart // on a aussi un port uart qui pointe vers notre pc
  reboot_SIM7080G();
  Serial.println("Around the World"); // CTRL + ALT + S
  setup_CATM1();
  periodX = millis();
}

void loop() {
  // put your main code here, to run repeatedly:
  everyX();
}

