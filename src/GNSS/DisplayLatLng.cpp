#include "DisplayLatLng.hpp"

void afficherCoordonnees(Coord coord) {
    Serial.print("Latitude : ");
    Serial.print(String (coord.latitude.ent));
    Serial.print(".");
    Serial.println(String (coord.latitude.dec));

    Serial.print("Longitude : ");
    Serial.print(String (coord.longitude.ent));
    Serial.print(".");
    Serial.println(String (coord.longitude.dec));
}
// void DisplayLatLngInfo(){
//     // String gnssData = get_GNSS_Info();
//     // String timeStamp = getTimeStamp(gnssData);
//     // Serial.println(convertTimestampToLocalTime(timeStamp, 1));
//     // return getLatLng(gnssData);
//     Gnss responsegGnss = getGnssResponse(); 
//     afficherCoordonnees(responsegGnss.coordonnees);
   
// }

void DisplayLatLngInfo(bool* afficherDepuisMemoire) {
    if (afficherDepuisMemoire && *afficherDepuisMemoire) {
        afficherCoordonneesDepuisEEPROM(afficherDepuisMemoire);
        return;
    }

    // Sinon : comportement classique
    Gnss responsegGnss = getGnssResponse(); 
    afficherCoordonnees(responsegGnss.coordonnees);

    Float_gnss lat = responsegGnss.coordonnees.latitude;
    Float_gnss lng = responsegGnss.coordonnees.longitude;
    String ts = responsegGnss.timeStamp;

    bool latValide = (lat.ent != 0 || lat.dec != 0);
    bool lngValide = (lng.ent != 0 || lng.dec != 0);
    bool timeStampValide = ts.length() > 0;

    // if (latValide && lngValide && timeStampValide) {
    if (latValide && lngValide ) {
        EEPROM.begin(EEPROM_SIZE);
        writeFloatGnss(ADDR_LATITUDE, lat);
        writeFloatGnss(ADDR_LONGITUDE, lng);
        // writeFloatGnss( ADDR_SIM_ID, lng);
        // writeFixedString(ADDR_TIMESTAMP, ts, 20);
        EEPROM.commit();
        Serial.println("Coordonnées et timeStamp enregistrés en EEPROM !");

        *afficherDepuisMemoire = true;  // ✅ Maintenant on peut passer en mode mémoire
    } else {
        Serial.println("Coordonnées invalides. Données NON enregistrées.");
    }
}

