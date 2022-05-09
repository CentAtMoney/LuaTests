// window_factory.h
#ifndef WINDOW_WINDOW_FACTORY_H
#define WINDOW_WINDOW_FACTORY_H

#include "window/window.h"

class window_factory
{
public:
    virtual ~window_factory() {}

    virtual window* create_glfw_window(const std::string& title, int width, int height);
};


#endif // WINDOW_WINDOW_FACTORY_H