#ifndef WINDOW_WINDOW_H
#define WINDOW_WINDOW_H

#include "publisher.h"

#include <string>
#include "graphics/extent.h"


using window_id = uint32_t;

// handle to some window implementation
class window : public publisher
{
public:
    struct create_info
    {
        std::string title;
        uint32_t width;
        uint32_t height;
    };
    window(window::create_info info);

    ~window();

    void poll();
    void swap_buffers();


    extent2d get_framebuffer_extent();

    // screen coordinates 
    extent2d get_window_extent();


private:

    window_id id_;

};
using window_t = window;

struct window_open_event
{
    window_t window;
};

struct window_close_event
{
    window_t window;
};

struct window_resize_event
{
    extent2d extent;
};

struct framebuffer_resize_event
{
    extent2d extent;
};

#endif // WINDOW_WINDOW_H