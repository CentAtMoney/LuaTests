#include "graphics/mesh.h"
#include "glad/gl.h"


mesh::mesh(std::vector<vertex> verticies, std::vector<uint32_t> indicies, std::vector<texture2d> textures) :
    verticies_{verticies_},
    indicies_{indicies},
    textures_{textures}
{
    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);

    glGenBuffers(1, &vbo_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER, verticies_.size() * sizeof(vertex), &verticies_[0], GL_STATIC_DRAW);

    glGenBuffers(1, &ebo_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies_.size() * sizeof(uint32_t), &indicies_[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*) offsetof(vertex, position));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*) offsetof(vertex, normal));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*) offsetof(vertex, tex_coord));

    glBindVertexArray(0);
}


void mesh::render(shader shader)
{
    
}