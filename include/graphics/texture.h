#ifndef GRAPHICS_TEXTURE_H
#define GRAPHICS_TEXTURE_H

#include "graphics/extent.h"

#include <string>

class texture2d
{
public:
    texture2d(const std::string& image_path);

    extent2d get_extent() const;


private:
    extent2d extent_;
    uint32_t id_;

};


#endif