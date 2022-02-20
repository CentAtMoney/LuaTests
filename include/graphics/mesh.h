#ifndef GRAPHICS_MESH_H
#define GRAPHICS_MESH_H

#include "graphics/texture.h"
#include "graphics/vertex.h"
#include "graphics/shader.h"

#include <vector>
#include <cstdint>

class mesh
{
public:
    mesh(std::vector<vertex> verticies, std::vector<uint32_t> indicies, std::vector<texture2d> textures);
    ~mesh();

    void render(shader shader);

    // if any changes are made to verticies_ or indicies_ this must be called to send
    // updated data to gpu. Must called at least once before mesh is rendered
    void buffer_data();

protected:
    std::vector<vertex> verticies_;
    std::vector<uint32_t> indicies_;
    std::vector<texture2d> textures_;

    uint32_t vao_, vbo_, ebo_;
};

// mesh of a rectangular prism with origin at geometric center of it
class cube_mesh : public mesh
{
public:
    cube_mesh(float length, float width, float depth, std::vector<texture2d> textures);
};


#endif