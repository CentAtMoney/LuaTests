// window.h
#ifndef WINDOW_WINDOW_H
#define WINDOW_WINDOW_H

#include "common.h"
#include "publisher.h"
#include "graphics/extent.h"


class window : public publisher
{
public:

    virtual ~window() {}

    virtual void poll() = 0;

    virtual void swap_buffers() = 0;

    virtual void disable_cursor() = 0;

    virtual void enable_cursor() = 0;

    virtual extent2d get_framebuffer_extent() = 0;

    // screen coordinates 
    virtual extent2d get_window_extent() = 0;

};



using window_t = window;

struct window_open_event
{
    window_t* window;
};

struct window_close_event
{
    window_t* window;
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