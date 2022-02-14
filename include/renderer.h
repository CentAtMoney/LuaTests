#ifndef RENDERER_H
#define RENDERER_H
#include "subscriber.h"
#include "graphics/shader.h"
#include <cstdint>
#include <glm/glm.hpp>

class renderer : public subscriber
{
public:
    renderer();
    ~renderer();

    void notify(const std::any& object) override;

    void render();

private:
    shader triangle_shader_;
    float* verticies_;
    uint32_t* indicies_;
    uint32_t vao_;
    uint32_t vbo_;
    uint32_t ebo_;
    glm::mat4 transform_;
    glm::vec3 normal_;
    int32_t transform_uniform_;

};

#endif