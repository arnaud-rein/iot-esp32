#include "GnssUtils.hpp"

Gnss getGNSSValid()
{
    Gnss responseGNSS = getGnssResponse();

    Float_gnss lat = responseGNSS.coordonnees.latitude;
    Float_gnss lng = responseGNSS.coordonnees.longitude;
    String ts = responseGNSS.timeStamp;

    bool latValide = ((lat.ent != 0) || lat.dec != 0);
    bool lngValide = ((lng.ent != 0) || lng.dec != 0);
    // bool latValide = ((lat.ent != 0 && lat.ent != 47) || lat.dec != 0);
    // bool lngValide = ((lng.ent != 0 && lng.ent != 4) || lng.dec != 0);

    if (latValide && lngValide)
    {
        responseGNSS.coordonnees.latitude.full = String(lat.ent) + "." + String(lat.dec);
        responseGNSS.coordonnees.longitude.full = String(lng.ent) + "." + String(lng.dec);
        responseGNSS.isValid = true;
    }

    return responseGNSS;
}

void shiftLeftDataGNSS(DataGNSS *array, int &nbCoordonnees)
{
    for (int i = 1; i < nbCoordonnees; ++i)
    {
        array[i - 1] = array[i];
    }
    nbCoordonnees--;
}

void addGNSSInDataGNSS(Gnss gnss)
{
    if (nbCoordonnees >= MAX_COORDS)
    {
        shiftLeftDataGNSS(dataGNSS, nbCoordonnees);
    }
    if (nbCoordonnees < MAX_COORDS)
    {
        dataGNSS[nbCoordonnees].gnss = gnss;
        nbCoordonnees++;
    }
}
