#include "SIM7080G_SERIAL.hpp"
// #include "ARGALI_PINOUT.hpp"


String Send_AT(String message, long delay){
  // Serial.println("millis début de Send_AT : " + (String) millis());
  
  unsigned long start_time = millis();
  Sim7080G.println(message);
  String uart_buffer = "";
  char tmp_char = 'A'; 
  while ((millis() - start_time < delay) && (uart_buffer.endsWith("OK") == false)  && (uart_buffer.endsWith("ACTIVE") == false))
  {
    /* code */
    if(Sim7080G.available()){
      tmp_char = Sim7080G.read();
      uart_buffer += tmp_char; 
      Serial.print(tmp_char);
      
    }

  }

  // Serial.println("millis fin de Send_AT : " + (String) millis());
  return uart_buffer; 
}