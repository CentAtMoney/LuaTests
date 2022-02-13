#include "application.h"

application::application(application::create_info info) :
    window_(info.window_create_info)
{
    window_.subscribe(this);
    this->subscribe(&this->renderer_);

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
        this->window_.poll();
    }
}

bool application::running() const
{
    return this->running_;
}
