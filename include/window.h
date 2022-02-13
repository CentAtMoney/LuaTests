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
        size_t height;
        size_t width;
    };
    window(window::create_info info);

    ~window();

private:

    window_id id_;

};


#endif // WINDOW_H