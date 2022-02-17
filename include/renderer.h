#ifndef RENDERER_H
#define RENDERER_H
#include "subscriber.h"
#include "graphics/shader.h"
#include "graphics/mesh.h"
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
    mesh* mesh_;
    glm::mat4 transform_;
    glm::vec3 normal_;
    int32_t transform_uniform_;

};

#endif