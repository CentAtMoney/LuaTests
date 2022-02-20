// renderer.cpp


#include "renderer.h"
#include "application.h"
#include "glad/gl.h"
#include "window/window.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include <iostream>

#include "stb_image.h"

void renderer::notify(const std::any& object)
{
    if(object.type() == typeid(framebuffer_resize_event))
    {
        framebuffer_resize_event event = std::any_cast<framebuffer_resize_event>(object);
        glViewport(0, 0, event.extent.width, event.extent.height);
        last_move_event_.x = ((float) event.extent.width) / 2.0f;
        last_move_event_.y = ((float) event.extent.height) / 2.0f;
        set_aspect_ratio(event.extent);
    }
    else if(object.type() == typeid(cursor_move_event))
    {
        cursor_move_event event = std::any_cast<cursor_move_event>(object);
        float dx = event.x - last_move_event_.x;
        float dy = event.y - last_move_event_.y;
        last_move_event_ = event;

        camera_.rotate(dy * sensitivity_, dx * sensitivity_, 0.0f);


    }
}


renderer::renderer() :
    triangle_shader_("../shaders/triangle.vert", "../shaders/triangle.frag"),
    mesh_(new cube_mesh(1.0f, 1.0f, 1.0f, {})),
    fov_(glm::radians(45.0f)),
    near_(0.1f),
    far_(100.0f),
    camera_(glm::vec3(-2.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)),
    model_(1.0f),
    sensitivity_(0.01f),
    projection_(glm::perspective(fov_, aspect_, near_, far_))
{
    mesh_->buffer_data();
}
renderer::~renderer()
{
    delete mesh_;
}

void renderer::set_fov(float fov)
{
    fov_ = fov;
    projection_ = glm::perspective(fov_, aspect_, near_, far_);
}

void renderer::set_aspect_ratio(float aspect)
{
    aspect_ = aspect;
    projection_ = glm::perspective(fov_, aspect_, near_, far_);
}
void renderer::set_aspect_ratio(extent2d extent)
{
    set_aspect_ratio(((float) extent.width) / ((float) extent.height));
}

void renderer::set_near_plane(float depth)
{
    near_ = depth;
    projection_ = glm::perspective(fov_, aspect_, near_, far_);
}

void renderer::set_far_plane(float depth)
{
    far_ = depth;
    projection_ = glm::perspective(fov_, aspect_, near_, far_);
}

void renderer::render()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glm::vec3 normal(0.5f, 1.0f, 0.3f);
    normal = glm::normalize(normal);
    model_ = glm::rotate(model_, glm::radians(.1f), normal);

    triangle_shader_.use();

    triangle_shader_.set_uniform("model", model_);
    triangle_shader_.set_uniform("view", camera_.get_view());
    triangle_shader_.set_uniform("projection", projection_);

    mesh_->render(triangle_shader_);

}