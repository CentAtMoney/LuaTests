#include "logger.h"
#include <iostream>

void Logger::log(std::string message)
{
    std::cout << "LOG: " << message << std::endl;
}