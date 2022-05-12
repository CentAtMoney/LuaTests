// glfw_window.h
#ifndef WINDOW_GLFW_WINDOW_H
#define WINDOW_GLFW_WINDOW_H

#include "common.h"

#include "window/window.h"

#include <GLFW/glfw3.h>

class glfw_window : public window
{
public:
    struct create_info
    {
        std::string title;
        uint32_t width;
        uint32_t height;
    };

    glfw_window(glfw_window::create_info);

    virtual ~glfw_window();
    
    virtual void poll() override;

    virtual void swap_buffers() override;

    virtual void disable_cursor() override;

    virtual void enable_cursor() override;

    virtual extent2d get_framebuffer_extent() override;

    // screen coordinates 
    virtual extent2d get_window_extent() override;


private:
    static int instance_count;

    GLFWwindow* glfw_window_;
};


#endif // WINDOW_GLFW_WINDOW_H