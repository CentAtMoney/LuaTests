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
    }
}


renderer::renderer() :
    triangle_shader_("../shaders/triangle.vert", "../shaders/triangle.frag"),
    transform_(1.0f),
    transform_uniform_(triangle_shader_.get_uniform_location("transform")),
    mesh_(new cube_mesh(1.0f, 1.0f, 1.0f, {})),
    normal_(1.0f, 1.0f, 1.0f)
{
    float m = normal_.length();
    normal_ /= m;

}
renderer::~renderer()
{
    delete mesh_;
}

void renderer::render()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    triangle_shader_.use();

    transform_ = glm::rotate(transform_, glm::radians(0.1f), normal_);

    glUniformMatrix4fv(transform_uniform_, 1, GL_FALSE, glm::value_ptr(transform_));

    mesh_->render(triangle_shader_);

}