#include "application.h"
#include "window/window_factory.h"
#include <iostream>
application::application(application::create_info info) :
    running_{true},
    publisher::publisher(info.subscribers),
    window_(nullptr),
    renderer_{}
{   
    window_factory window_factory;
    window_factory.create_glfw_window("glfw window", 800, 600);

    this->window_->disable_cursor();

    // application subscribes to window events
    this->window_->subscribe(this);

    // renderer subscribes to application events
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
    this->publish(object);

    //std::cout << "application event: " << object.type().name() << std::endl;
}

void application::run()
{
    while(this->running())
    {
        this->window_->poll();
        this->renderer_.render();
        this->window_->swap_buffers();
    }
}

bool application::running() const
{
    return this->running_;
}
