#include "Logger.h"

Logger::Logger(std::string name)
{
    name_ = name;
    file_.open(name_, std::ios::out);
}

Logger::~Logger()
{
    file_.close();
}

void Logger::print(std::string message)
{
    file_ << message;
}

void Logger::print_line(std::string message)
{
    file_ << message << std::endl;
}