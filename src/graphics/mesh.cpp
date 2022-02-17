// mesh.cpp

#include "graphics/mesh.h"
#include "glad/gl.h"


mesh::mesh(std::vector<vertex> verticies, std::vector<uint32_t> indicies, std::vector<texture2d> textures) :
    verticies_{verticies},
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


mesh::~mesh()
{
    glDeleteVertexArrays(1, &vao_);
    glDeleteBuffers(1, &vbo_);
    glDeleteBuffers(1, &ebo_);
}

void mesh::render(shader shader)
{
    // TODO textures :)
    glBindVertexArray(vao_);
    glDrawElements(GL_TRIANGLES, indicies_.size(), GL_UNSIGNED_INT, 0);
}


cube_mesh::cube_mesh(float l, float w, float d, std::vector<texture2d> textures) :
    mesh(std::vector<vertex>(24), std::vector<uint32_t>(36), textures)
{

    // create 8 position verticies
    // do we have to normalize these?
    glm::vec3 p1( l/2,  w/2,  d/2);
    glm::vec3 p2( l/2, -w/2,  d/2);
    glm::vec3 p3(-l/2, -w/2,  d/2);
    glm::vec3 p4(-l/2,  w/2,  d/2);
    glm::vec3 p5(-l/2,  w/2, -d/2);
    glm::vec3 p6(-l/2, -w/2, -d/2);
    glm::vec3 p7( l/2, -w/2, -d/2);
    glm::vec3 p8( l/2,  w/2, -d/2);

    // create 6 normal vectors
    glm::vec3 n1( 1.0f,  0.0f,  0.0f);
    glm::vec3 n2( 0.0f,  0.0f,  1.0f);
    glm::vec3 n3(-1.0f,  0.0f,  0.0f);
    glm::vec3 n4( 0.0f,  0.0f, -1.0f);
    glm::vec3 n5( 0.0f,  1.0f,  0.0f);
    glm::vec3 n6( 0.0f, -1.0f,  0.0f);

    // create 4 texture coordinates
    glm::vec2 bl(0.0f, 0.0f);
    glm::vec2 br(1.0f, 0.0f);
    glm::vec2 tl(0.0f, 1.0f);
    glm::vec2 tr(1.0f, 1.0f);

    // +x (n1) verticies
    verticies_[0]  = vertex(p1, n1, tl);
    verticies_[1]  = vertex(p8, n1, tr);
    verticies_[2]  = vertex(p2, n1, bl);
    verticies_[3]  = vertex(p7, n1, br);

    // 6 +x indicies
    indicies_[0]  = 0;
    indicies_[1]  = 1;
    indicies_[2]  = 2;
    indicies_[3]  = 1;
    indicies_[4]  = 2;
    indicies_[5]  = 3;

    // +z (n2) verticies
    verticies_[4]  = vertex(p4, n2, tl);
    verticies_[5]  = vertex(p1, n2, tr);
    verticies_[6]  = vertex(p3, n2, bl);
    verticies_[7]  = vertex(p2, n2, br);

    // 6 +z indicies
    indicies_[6]  = 4;
    indicies_[7]  = 5;
    indicies_[8]  = 6;
    indicies_[9]  = 5;
    indicies_[10] = 6;
    indicies_[11] = 7;

    // -x (n3) verticies
    verticies_[8]  = vertex(p5, n3, tl);
    verticies_[9]  = vertex(p4, n3, tr);
    verticies_[10] = vertex(p6, n3, bl);
    verticies_[11] = vertex(p3, n3, br);

    // 6 -x indicies
    indicies_[12]  = 8;
    indicies_[13]  = 9;
    indicies_[14]  = 10;
    indicies_[15]  = 9;
    indicies_[16]  = 10;
    indicies_[17]  = 11;

    // -z (n4) verticies
    verticies_[12] = vertex(p8, n4, tl);
    verticies_[13] = vertex(p5, n4, tr);
    verticies_[14] = vertex(p7, n4, bl);
    verticies_[15] = vertex(p6, n4, br);

    // 6 -z indicies
    indicies_[18]  = 12;
    indicies_[19]  = 13;
    indicies_[20]  = 14;
    indicies_[21]  = 13;
    indicies_[22]  = 14;
    indicies_[23]  = 15;

    // +y (n5) verticies
    verticies_[16] = vertex(p1, n5, tl);
    verticies_[17] = vertex(p4, n5, tr);
    verticies_[18] = vertex(p8, n5, bl);
    verticies_[19] = vertex(p5, n5, br);

    // 6 +y indicies
    indicies_[24]  = 16;
    indicies_[25]  = 17;
    indicies_[26]  = 18;
    indicies_[27]  = 17;
    indicies_[28]  = 18;
    indicies_[29]  = 19;

    // -y (n6) verticies
    verticies_[20] = vertex(p6, n6, tl);
    verticies_[21] = vertex(p7, n6, tr);
    verticies_[22] = vertex(p3, n6, bl);
    verticies_[23] = vertex(p2, n6, br);

    // 6 -y indicies
    indicies_[30]  = 20;
    indicies_[31]  = 21;
    indicies_[32]  = 22;
    indicies_[33]  = 21;
    indicies_[34]  = 22;
    indicies_[35]  = 23;

    
}


