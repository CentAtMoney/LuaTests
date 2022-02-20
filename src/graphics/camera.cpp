// camera.cpp
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "graphics/camera.h"

camera::camera(glm::vec3 pos, glm::vec3 target, glm::vec3 up) :
    pos_(pos),
    target_(target),
    up_(up)
{
}

glm::mat4 camera::get_view() const
{
    return glm::lookAt(pos_, target_, up_);
}

glm::vec3 camera::get_pos() const
{
    return pos_;
}

glm::vec3 camera::get_target() const
{
    return target_;
}

glm::vec3 camera::get_up() const
{
    return up_;
}

void camera::set_pos(glm::vec3 pos)
{
    pos_ = pos;
}

void camera::set_target(glm::vec3 target)
{
    target_ = target;
}

void camera::set_up(glm::vec3 up)
{
    up_ = up;
}

void camera::rotate(float pitch, float yaw, float roll)
{
    glm::vec3 euler_angles(pitch, yaw, roll);
    glm::quat quat(euler_angles);

    target_ = glm::normalize(glm::mat3_cast(quat) * target_);
}