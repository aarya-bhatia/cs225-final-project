#include "K.h"

namespace K
{
    const std::string AIRPORTS_FILE = "res/OpenFlights/airports.dat.csv";
    const std::string ROUTES_FILE = "res/OpenFlights/routes.dat.csv";

    /* Airport dataset column index */
    const unsigned int AIRPORT_NAME = 1;
    const unsigned int AIRPORT_CITY = 2;
    const unsigned int AIRPORT_COUNTRY = 3;
    const unsigned int AIRPORT_IATA = 4;
    const unsigned int AIRPORT_ICAO = 5;
    const unsigned int AIRPORT_LATITUDE = 6;
    const unsigned int AIRPORT_LONGITUDE = 7;

    /* Routes dataset column index */
    const unsigned int ROUTES_SOURCE_AIRPORT = 2;
    const unsigned int ROUTES_DESTINATION_AIRPORT = 4;

    extern const float EARTH_RADIUS = 6371; /* In KM */
}