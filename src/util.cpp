#include "util.h"
#include <stdexcept>
#include <algorithm>
#include <sstream>
#include <cmath>
#include "K.h"

static bool debug_util = false;

namespace util
{
    std::vector<std::string> parse_line(const std::string &line)
    {
        if(debug_util) std::cout << __LINE__ << ":Line: " << line << std::endl;

        // to check if word is inside quote
        bool has_quote = false;

        std::vector<std::string> tokens;

        // store built word
        std::string word = "";

        for(size_t i = 0; i < line.length(); i++)
        {
            char c = line[i];

            // begin or end quote
            if(c == '"')
            {
                has_quote = !has_quote;
            }
            else if(c == ',')
            {
                // comma inside quotes is part of word
                if(has_quote)
                {
                    word += c;
                }
                // otherwise we reached end of word
                else
                {
                    tokens.push_back(trim(word));
                    word = "";
                }
            }
            else
            {
                // Any other character
                word += c;
            }
        }

        // word after last comma
        if(!word.empty())
        {
            tokens.push_back(trim(word));
        }

        return tokens;
    }

    std::vector<std::vector<std::string>> parse_csv_file(std::string filename)
    {
        std::ifstream file(filename);

        if (!file.is_open())
        {
            throw std::runtime_error("Could not open file: " + filename);
        }

        std::vector<std::vector<std::string>> lines;
        std::string line; // store current line

        // Line count
        int c = 0; 

        while (std::getline(file, line))
        {
            std::vector<std::string> tokens = parse_line(line);
            lines.push_back(tokens);

            if(debug_util) std::cout << tokens.size() << " tokens line " << c++ << std::endl;
        }

        file.close();

        return lines;
    }

    std::string ltrim(const std::string &s)
    {
        size_t start = s.find_first_not_of(WHITESPACE);
        return (start == std::string::npos) ? "" : s.substr(start);
    }

    std::string rtrim(const std::string &s)
    {
        size_t end = s.find_last_not_of(WHITESPACE);
        return (end == std::string::npos) ? "" : s.substr(0, end + 1);
    }

    std::string trim(const std::string &s)
    {
        return rtrim(ltrim(s));
    }

    std::string to_upper_case(const std::string &s)
    {
        std::string res = "";

        for(const char &c: s)
        {
            if(c >= 'a' && c <= 'z')
            {
                res += 'A' + c - 'a';
            }
            else
            {
                res += c;
            }
        }

        return res;
    }


    std::string to_lower_case(const std::string &s)
    {
        std::string res = "";

        for(const char &c: s)
        {
            if(c >= 'A' && c <= 'Z')
            {
                res += 'a' + c - 'A';
            }
            else
            {
                res += c;
            }
        }

        return res;
    }

    float degree_to_radians(float angle)
    {
        return angle * M_PI / 180.0f;
    }

    float haversine(float angle)
    {
        return pow(sin(angle/2),2);
    }

    float distance(float lat1, float lon1, float lat2, float lon2)
    {
        lat1 = degree_to_radians(lat1);
        lon1 = degree_to_radians(lon1);
        lat2 = degree_to_radians(lat2);
        lon2 = degree_to_radians(lon2);

        float delta_lat = haversine(lat2 - lat1);
        float delta_lon = haversine(lon2 - lon1);

        float a = delta_lat + cos(lat1) * cos(lat2) * delta_lon;

        float c = 2 * asin(sqrt(a));

        return c * K::EARTH_RADIUS;
    }

    std::string to_string(const std::vector<std::string> &v)
    {
        std::stringstream ss;

        ss << "< ";

        for(size_t i = 0; i < v.size(); i++)
        {
            ss << '<' << v[i] << '>' << " ";
        }

        ss << ">";

        return ss.str();
    }

    std::string to_string(const std::vector<char> &v)
    {
        std::stringstream ss;

        ss << "< ";

        for(size_t i = 0; i < v.size(); i++)
        {
            ss << '<' << v[i] << '>' << " ";
        }

        ss << ">";

        return ss.str();
    }

}
