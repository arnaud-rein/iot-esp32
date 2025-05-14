#include "DisplayLatLng.hpp"

void afficherCoordonnees(Coord coord)
{
    Serial.print("Latitude : ");
    Serial.print(String(coord.latitude.ent));
    Serial.print(".");
    Serial.println(String(coord.latitude.dec));

    Serial.print("Longitude : ");
    Serial.print(String(coord.longitude.ent));
    Serial.print(".");
    Serial.println(String(coord.longitude.dec));
}
// void DisplayLatLngInfo(){
//     // String gnssData = get_GNSS_Info();
//     // String timeStamp = getTimeStamp(gnssData);
//     // Serial.println(convertTimestampToLocalTime(timeStamp, 1));
//     // return getLatLng(gnssData);
//     Gnss responsegGnss = getGnssResponse();
//     afficherCoordonnees(responsegGnss.coordonnees);

// }

void DisplayLatLngInfo(bool *afficherDepuisMemoire)
{
    if (afficherDepuisMemoire && *afficherDepuisMemoire)
    {
        afficherCoordonneesDepuisEEPROM(afficherDepuisMemoire);
        return;
    }

    // Sinon : comportement classique
    Gnss responsegGnss = getGnssResponse();
    afficherCoordonnees(responsegGnss.coordonnees);

    Float_gnss lat = responsegGnss.coordonnees.latitude;
    Float_gnss lng = responsegGnss.coordonnees.longitude;
    String ts = responsegGnss.timeStamp;

    bool latValide = ((lat.ent != 0) || lat.dec != 0);
    bool lngValide = ((lng.ent != 0) || lng.dec != 0);
    // bool latValide = ((lat.ent != 0 && lat.ent != 47) || lat.dec != 0);
    // bool lngValide = ((lng.ent != 0 && lng.ent != 4) || lng.dec != 0);
    bool timeStampValide = ts.length() > 0;

    // if (latValide && lngValide ) {
    // if (latValide && lngValide && timeStampValide) {
    Serial.println("Coordonnées => latitude : " + String(lat.ent) + "." + String(lat.dec) + " longitude : " + String(lng.ent) + "." + String(lng.dec));
    if (latValide && lngValide)
    {
        EEPROM.begin(EEPROM_SIZE);
        writeFloatGnss(ADDR_LATITUDE, lat);
        writeFloatGnss(ADDR_LONGITUDE, lng);
        // writeFloatGnss( ADDR_SIM_ID, lng);
        // writeFixedString(ADDR_TIMESTAMP, ts, 20);
        EEPROM.commit();
        Serial.println("Coordonnées et timeStamp enregistrés en EEPROM !");

        String latitude = String(lat.ent) + "." + String(lat.dec);
        String longitude = String(lng.ent) + "." + String(lng.dec);

        String result = String("{\"name\":\"") + "testets" + "\",\"position\":{\"latitude\":" + latitude + ",\"longitude\":" + longitude + "}}";
        // Pour ajouter un message
        MessageCoord msg;
        msg.data = result;
        msg.endCBOR = true;
        if (listeCoordonnees.size() >= 5)
        {
            listeCoordonnees.erase(listeCoordonnees.begin());
        }
        listeCoordonnees.push_back(msg);

        *afficherDepuisMemoire = false; // ✅ Maintenant on peut passer en mode mémoire
    }
    else
    {
        Serial.println("Coordonnées invalides. Données NON enregistrées.");
    }
}
