#ifndef LOGGER_H
#define LOGGER_H

#include <string>


class logger
{
public:
    void log(const std::string message);

    logger* get_instance();
private:
    logger();

};

#endif