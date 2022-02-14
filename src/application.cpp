#include "application.h"

application::application(application::create_info info) :
    window_(info.window_create_info),
    publisher::publisher(info.subscribers),
    renderer_{},
    running_{true}
{   

    // application subscribes to window events
    this->window_.subscribe(this);

    // renderer subscribes to window events
    this->window_.subscribe(&this->renderer_);

    window_create_event window_create_event = {
        .window = this->window_
    };
    this->publish(window_create_event);


}

application::~application()
{

}

void application::notify(const std::any& object)
{
    if(object.type() == typeid(window_close_event))
    {
        this->running_ = false;
    }
}

void application::run()
{
    while(this->running())
    {
        this->renderer_.render();
        this->window_.swap_buffers();
        this->window_.poll();
    }
}

bool application::running() const
{
    return this->running_;
}
