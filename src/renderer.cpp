#include "renderer.h"
#include "application.h"
#include "glad/gl.h"
#include "window/window.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include <iostream>

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
    normal_(0.0f, 0.0f, 1.0f),
    transform_uniform_(triangle_shader_.get_uniform_location("transform")),
    verticies_(new float[] {
         0.5f,  0.0f, 0.0f, //right
         0.0f,  0.5f, 0.0f, //top
        -0.5f,  0.0f, 0.0f, //left
         0.0f, -0.5f, 0.0f  //bottom
    }),
    indicies_(new uint32_t[] {
        0, 1, 2,
        0, 3, 2
    })
{

    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);

    glGenBuffers(1, &vbo_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), verticies_, GL_STATIC_DRAW);

    glGenBuffers(1, &ebo_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(float), indicies_, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);


}
renderer::~renderer()
{
    glDeleteVertexArrays(1, &vao_);
    glDeleteBuffers(1, &vbo_);
    glDeleteBuffers(1, &ebo_);
    delete[] this->verticies_;
    delete[] this->indicies_;
}

void renderer::render()
{

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    triangle_shader_.use();


    transform_ = glm::rotate(transform_, glm::radians(0.1f), normal_);
    glUniformMatrix4fv(transform_uniform_, 1, GL_FALSE, glm::value_ptr(transform_));


    glBindVertexArray(vao_);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


}