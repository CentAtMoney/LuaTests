#ifndef WINDOW_H
#define WINDOW_H

#include "publisher.h"

#include <string>

using window_id = uint32_t;


class window : public publisher
{
public:
    struct create_info
    {
        std::string title;
        size_t width;
        size_t height;
    };
    window(window::create_info info);

    ~window();

    void poll();
    void swap_buffers();

private:

    window_id id_;

};

struct window_open_event
{
    window window;
};

struct window_close_event
{
    window window;
};

#endif // WINDOW_H