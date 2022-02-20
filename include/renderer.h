#ifndef RENDERER_H
#define RENDERER_H
#include "subscriber.h"
#include "graphics/shader.h"
#include "graphics/mesh.h"
#include "graphics/camera.h"
#include <cstdint>
#include <glm/glm.hpp>
#include "input.h"

class renderer : public subscriber
{
public:
    renderer();
    ~renderer();

    void notify(const std::any& object) override;

    void render();

    void set_fov(float fov);
    void set_aspect_ratio(float aspect);
    void set_aspect_ratio(extent2d extent);
    void set_near_plane(float depth);
    void set_far_plane(float depth);

private:

    glm::vec3 camera_pos_;

    shader triangle_shader_;
    mesh* mesh_;

    float fov_;
    float aspect_;
    float near_;
    float far_;

    glm::mat4 model_;

    camera camera_;
    float sensitivity_;
    cursor_move_event last_move_event_;


    glm::mat4 projection_;

};

#endif