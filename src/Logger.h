/**
 * A file logger class to write output to a file.
 * @file Log.h
 */
#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

class Logger
{
    public:
        Logger(std::string name);
        ~Logger();

        void print(std::string message); 
        void print_line(std::string message); 

    private:
        std::string name_;
        std::ofstream file_;
};

#endif