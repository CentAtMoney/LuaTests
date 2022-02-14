#ifndef APPLICATION_H
#define APPLICATION_H

#include "renderer.h"
#include "publisher.h"
#include "subscriber.h"
#include "window/window.h"
#include "logger.h"

#include <string>
#include <vector>

struct window_create_event
{
    window_t* window;
};

class application : public publisher, subscriber
{
public:
    struct create_info
    {
        window::create_info window_create_info;
        std::vector<subscriber*> subscribers;
    };
    application(application::create_info info);
    ~application();
    
    void notify(const std::any& object) override;

    void run();

    bool running() const;

private:
    window window_;
    renderer renderer_;
    bool running_;
};


#endif