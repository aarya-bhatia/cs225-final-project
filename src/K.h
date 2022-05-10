/**
 * Constants are defined in this namespace.
 */

#ifndef K_H
#define K_H

#include <string>

namespace K
{
    extern const std::string AIRPORTS_FILE;
    extern const std::string ROUTES_FILE;

    /* Airport dataset column index */
    extern const unsigned int AIRPORT_NAME;
    extern const unsigned int AIRPORT_CITY;
    extern const unsigned int AIRPORT_COUNTRY;
    extern const unsigned int AIRPORT_IATA;
    extern const unsigned int AIRPORT_ICAO;
    extern const unsigned int AIRPORT_LATITUDE;
    extern const unsigned int AIRPORT_LONGITUDE;

    /* Routes dataset column index */
    extern const unsigned int ROUTES_SOURCE_AIRPORT;
    extern const unsigned int ROUTES_DESTINATION_AIRPORT;

    extern const float EARTH_RADIUS; /* In KM */
    
};

#endif
