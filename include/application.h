#ifndef APPLICATION_H
#define APPLICATION_H

#include "publisher.h"
#include "window.h"
#include "logger.h"

#include <string>


class application : public publisher
{
public:
    struct create_info
    {
        window::create_info window_create_info;
    };
    application(application::create_info info);
    ~application();

private:
    window window_;
};


#endif