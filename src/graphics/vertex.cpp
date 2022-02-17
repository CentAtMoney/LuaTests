// vertex.cpp

#include "graphics/vertex.h"

vertex::vertex()
{

}
vertex::vertex(const vertex& vertex) :
position(vertex.position),
normal(vertex.position),
tex_coord(vertex.position)
{

}

vertex::vertex(float x, float y, float z, float nx, float ny, float nz, float s, float t) :
    position(x, y, z),
    normal(nx, ny, nz),
    tex_coord(s, t)
{
}

vertex::vertex(glm::vec3 position, glm::vec3 normal, glm::vec2 tex_coord) :
    position(position),
    normal(normal),
    tex_coord(tex_coord)
{
}