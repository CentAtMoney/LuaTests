#ifndef APPLICATION_H
#define APPLICATION_H

#include "renderer.h"
#include "publisher.h"
#include "subscriber.h"
#include "window.h"
#include "logger.h"

#include <string>

struct window_create_event
{
    window window;
};

class application : public publisher, subscriber
{
public:
    struct create_info
    {
        window::create_info window_create_info;
    };
    application(application::create_info info);
    ~application();
    
    void notify(const std::any& object) override;

    void run();

    bool running() const;

private:
    bool running_;
    renderer renderer_;
    window window_;
};


#endif