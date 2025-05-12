#include "SIM7080G_CATM1.hpp"

void setup_CATM1()
{
    //You must turn off GNSS before turning on CATM1
    // gnssTurnOff();

    //see datasheet
    Send_AT("AT+CNMP=38");

    /*
    WARNING on the ARGALI SIM C3 V1.0 the SIMCOM processor used is
    SIM7080G-M that does not feature NB-IOT.
    1 -> CAT-M1 et 2 -> NB-IOT
    */
    Send_AT("AT+CMNB=1");

    //APP Network Deactive(PDP context)
    Send_AT("AT+CNACT=0,0");

    //paramétrage de l'APN (Access Point Name)
    Send_AT("AT+CGDCONT=1,\"IP\",\"iot.1nce.net\"");
    Send_AT("AT+CGNAPN");
    Send_AT("AT+CNCFG=0,1,iot.1nce.net");

    /*
    We wait for the SIM7080G to register to the local 4G antenna
    Correct registration : 
    AT+CEREG?
    +CEREG: 0,5
    */
    Send_AT("AT+CEREG?");

    //APP Network Active (PDP context)
    //You should wait for a valid response : +APP PDP: 0,ACTIVE
    String resultPDP = findSelect(Send_AT("AT+CNACT=0,1", 15000), "PDP", 4, ",", " ");
    if(resultPDP == "ACTIVE" ){
        Serial.print("ACTIVE detecté");
    }

    //informations for you on CAT-M1 connexion
    Send_AT("AT+CGATT?");
    Send_AT("AT+CNACT?", 3000);
    String resultCNACT = findSelect(Send_AT("AT+CNACT?", 3000), "+CNACT:", 12, "\"", ".");
    if(resultCNACT == "10"){
        Serial.println("10 detecté");
    }
    Send_AT("AT+GSN");
    Send_AT("AT+CCID");
    Send_AT("AT+COPS?");
    Send_AT("AT+CEREG?");
    //signal quality
    Send_AT("AT+CSQ");
}

void loop_CATM1() // vérifie que c'est bien connecté via la connexion = 5
{
    if(findSelect(Send_AT("AT+CEREG?"), "+CEREG:", 9, ",", " ") == "5"){
        Serial.println("5 condition");
        // TCP_send();
    }
    Send_AT("AT+CSQ");
    // csqNumber(Send_AT("AT+CSQ"));
}


void period10000function(){
    if((millis() - period100000) > 10000){
       Serial.println("--");
       Serial.println("--");
       Serial.println("");
       Serial.print("[");
       Serial.print(millis());
       Serial.print("ms]" );
       Serial.println("");
       Serial.println("--");
       Serial.println("--");
       period100000 = millis();
     }
}



String findSelect(String data, String nameStart, int numberPassAfterNameStart, String symbolToSelectStart, String symbolToEnd){
    Serial.print("millis de findSelect" + (String) millis());
    int indexStart = data.indexOf(nameStart, 0);
    int indexAfterStart = indexStart + numberPassAfterNameStart; 
    int indexSymbolStart = data.indexOf(symbolToSelectStart, indexAfterStart);
    int numberBetween_symbolStart_symbolEnd = data.indexOf(symbolToEnd, indexSymbolStart + 1);
    String result = data.substring(indexSymbolStart + 1, numberBetween_symbolStart_symbolEnd);
    Serial.println(" voici le findSelect");
    Serial.println("=============data : " + data);
    Serial.println("indexStart: " + (String) indexStart);
    Serial.println("indexAfterStart: " + (String) indexAfterStart);
    Serial.println("indexSymbolStart: " + (String) indexSymbolStart);
    Serial.println("numberBetween_symbolStart_symbolEnd: " + (String) numberBetween_symbolStart_symbolEnd);
    Serial.println("résultat : " + result);
    return result; 
}
