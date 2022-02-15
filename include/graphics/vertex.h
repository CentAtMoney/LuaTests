#ifndef GRAPHICS_VERTEX_H
#define GRAPHICS_VERTEX_H

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

struct vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 tex_coord;
};

#endif // GRAPHICS_VERTEX_H
