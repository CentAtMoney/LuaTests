#include "logger.h"
#include <iostream>

void logger::log(std::string message)
{
    std::cout << "LOG: " << message << std::endl;
}