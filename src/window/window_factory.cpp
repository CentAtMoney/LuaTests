// window_factory.cpp
#include "window/window_factory.h"
#include "window/glfw_window.h"

window* window_factory::create_glfw_window(const std::string& title, int width, int height)
{
    glfw_window::create_info create_info = {
        .title = title, 
        .width = width, 
        .height = height
    };
    return new glfw_window(create_info);
}