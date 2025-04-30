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
void DisplayLatLngInfo(){
    // String gnssData = get_GNSS_Info();
    // String timeStamp = getTimeStamp(gnssData);
    // Serial.println(convertTimestampToLocalTime(timeStamp, 1));
    // return getLatLng(gnssData);
    Gnss responsegGnss = getGnssResponse(); 
    afficherCoordonnees(responsegGnss.coordonnees);
   
}
