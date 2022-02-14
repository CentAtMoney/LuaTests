#ifndef GRAPHICS_EXTENT_H
#define GRAPHICS_EXTENT_H
#include <cstdint>

struct extent2d
{
    uint32_t width;
    uint32_t height;
};

struct extent3d
{
    uint32_t width;
    uint32_t height;
    uint32_t depth;
};

#endif // GRAPHICS_EXTENT_H