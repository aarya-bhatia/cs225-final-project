#ifndef AIRPORT_H
#define AIRPORT_H

#include <string>

class Airport
{
    public:
        Airport()
        {
        }

        std::string name;
        std::string city;
        std::string country;
        float latitude;
        float longitude;
};

#endif