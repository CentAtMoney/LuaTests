#ifndef GRAPHICS_VERTEX_H
#define GRAPHICS_VERTEX_H

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

struct vertex
{
    vertex();
    vertex(const vertex& vertex);
    vertex(float x, float y, float z, float nx, float ny, float nz, float s, float t);
    vertex(glm::vec3 position, glm::vec3 normal, glm::vec2 tex_coord);

    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 tex_coord;
};



#endif // GRAPHICS_VERTEX_H
