// camera.cpp
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "graphics/camera.h"

#include <iostream>
camera::camera(glm::vec3 pos, glm::vec3 front, glm::vec3 up) :
    pos_(pos),
    front_(front),
    up_(up)
{
    

}

glm::mat4 camera::get_view() const
{
    return glm::lookAt(pos_, get_target(), up_);
}

glm::vec3 camera::get_pos() const
{
    return pos_;
}

glm::vec3 camera::get_front() const
{
    return front_;
}

glm::vec3 camera::get_up() const
{
    return up_;
}

glm::vec3 camera::get_target() const
{
    return pos_ + front_;
}

void camera::set_pos(glm::vec3 pos)
{
    pos_ = pos;
}

void camera::set_front(glm::vec3 front)
{
    front_ = front;
}

void camera::set_up(glm::vec3 up)
{
    up_ = up;
}

void camera::rotate(float pitch, float yaw, float roll)
{
    glm::vec3 right = glm::normalize(glm::cross(front_, up_));
    front_ = glm::rotate(front_, pitch, right);
    front_ = glm::rotate(front_, yaw, up_);
    front_ = glm::rotate(front_, roll, front_);
}


void camera::move(glm::vec3 dx)
{
    pos_ += dx;
}
