#include "SIM7080G_GNSS.hpp"

DataGNSS dataGNSS[MAX_COORDS];
String gnssTurnOn()
{
    return Send_AT("AT+CGNSPWR=1"); // Envoie la commande AT+CBC
}

String gnssTurnOff()
{
    return Send_AT("AT+CGNSPWR=0"); // Envoie la commande AT+CBC
}

String check_GNSS_Status()
{
    return Send_AT("AT+CGNSPWR?");
}

String get_GNSS_Info()
{
    return Send_AT("AT+CGNSINF");
}
String get_GNSS_Mode()
{
    return Send_AT("AT+CGNSMOD=1,0,0,1,0");
}

String getValueOfGnssData(String gnssData, int16_t choiceValue)
{
    int index = 0; // Compteur pour suivre le nombre de valeurs extraites
    int start = 0; // Position de départ pour extraire une valeur
    int end = 0;   // Position de fin de la valeur extraite

    String values[19]; // Tableau pour stocker les différentes valeurs séparées par des virgules

    // Boucle pour parcourir toute la chaîne et extraire les valeurs une par une
    while ((end = gnssData.indexOf(',', start)) != -1 && index < 19)
    {
        // Extraire la sous-chaîne entre "start" et la première virgule trouvée
        values[index++] = gnssData.substring(start, end);
        // Déplacer "start" après la virgule pour la prochaine extraction
        start = end + 1;
    }

    return values[choiceValue];
}

String getRunStatus(String gnssData)
{
    return getValueOfGnssData(gnssData, 0);
}

String getFixStatus(String gnssData)
{
    return getValueOfGnssData(gnssData, 1);
}

String getTimeStamp(String gnssData)
{
    return getValueOfGnssData(gnssData, 2);
}

String getLat(String gnssData)
{
    return getValueOfGnssData(gnssData, 3);
}

String getLng(String gnssData)
{
    return getValueOfGnssData(gnssData, 4);
}

String getAltitude(String gnssData)
{
    return getValueOfGnssData(gnssData, 5);
}

Coord parserLatLng(String lat, String lng)
{
    Coord coord;
    coord.latitude = parseGNSS(lat);
    coord.longitude = parseGNSS(lng);
    return coord;
}

Float_gnss parseGNSS(String coord)
{
    Float_gnss result;

    int pointIndex = coord.indexOf('.');

    if (pointIndex == -1)
    {
        Serial.println("Erreur : Format invalide !");
        return result;
    }

    result.ent = coord.substring(0, pointIndex).toInt();

    int commaIndex = coord.indexOf(',', pointIndex);
    if (commaIndex == -1)
        result.dec = coord.substring(pointIndex + 1);
    else
        result.dec = coord.substring(pointIndex + 1, commaIndex);

    result.full = coord.substring(0, (commaIndex == -1 ? coord.length() : commaIndex));

    Serial.println("Coordonnée entière : " + String(result.ent));
    Serial.println("Coordonnée décimale (complète) : " + result.dec);
    Serial.println("Coordonnée complète extraite : " + result.full);

    return result;
}

Gnss getGnssResponse()
{
    Gnss gnss;
    String gnssData = get_GNSS_Info();
    Coord coord = parserLatLng(getLat(gnssData), getLng(gnssData));
    gnss.runStatus = getRunStatus(gnssData);
    gnss.fixStatus = getFixStatus(gnssData);
    gnss.timeStamp = getTimeStamp(gnssData);
    gnss.coordonnees = coord;
    gnss.altitude = getAltitude(gnssData);

    return gnss;
}
