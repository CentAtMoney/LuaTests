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

    void render(shader shader);

private:
    std::vector<vertex> verticies_;
    std::vector<uint32_t> indicies_;
    std::vector<texture2d> textures_;

    uint32_t vao_, vbo_, ebo_;

};

#endif