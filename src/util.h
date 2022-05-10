#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

namespace util
{
    /* whitespace characters */
    static const std::string WHITESPACE = " \n\r\t\f\v";

    /**
     * Removes the whitespaces on the left end of a string
     */
    std::string ltrim(const std::string &s);

    /**
     * Removes the whitespaces on the right end of a string
     */
    std::string rtrim(const std::string &s);

    /**
     * Removes the whitespaces from both ends of a string
     */
    std::string trim(const std::string &s);

    /**
     * @param filename path of csv file
     * @return A collection of lists of strings from each line of the csv file
     */
    std::vector<std::vector<std::string>> parse_csv_file(std::string filename);

    /**
     * Splits a sentence into its counterparts separated by commas.
     * Also, separates strings surrounded by quotations.
     */
    std::vector<std::string> parse_line(const std::string &line);

    std::string to_string(const std::vector<std::string> &s);

    std::string to_upper_case(const std::string &s);
    std::string to_lower_case(const std::string &s);

    /**
     * @param v The given vector
     * @return string representation of vector
     */
    std::string to_string(const std::vector<std::string> &v);
    std::string to_string(const std::vector<char> &v);

    /**
     * @param angle angle in degrees
     * @return angle in radian
     */
    float degree_to_radians(float angle);

    /**
     * @param angle in radians
     * @returns sin^2(angle/2)
     */
    float haversine(float angle);

    /**
     * All parameters are in degrees.
     * @param lat1 latitude of source coord
     * @param lon1 longitutde of source coord
     * @param lat2 latitude of dest coord
     * @param lon2 longitutde of dest coord
     * @return distance between the given coordinates on earth surface
     */
    float distance(float lat1, float lon1, float lat2, float lon2);

};

#endif
