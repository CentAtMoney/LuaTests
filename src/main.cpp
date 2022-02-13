
#include "shader.h"
#include "application.h"

#include "glad/gl.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include <typeinfo>
#include <typeindex>
#include <vector>
#include <any>



void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main(int argc, char** argv)
{

    application::create_info application_create_info;
    application_create_info.window_create_info = {
        .title = "LuaTest",
        .width = 800,
        .height = 600,
    };


    application app();


    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    GLFWwindow* window = glfwCreateWindow(800, 600, "Window Name", NULL, NULL);
    if(!window) {
        glfwTerminate();
        std::cout << "glfw window failed to create\n";
        return -1;
    }

    glfwMakeContextCurrent(window);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    gladLoadGL(glfwGetProcAddress);



    glViewport(0, 0, 800, 600);

    shader triangleShader("../shaders/triangle.vert", "../shaders/triangle.frag");


    float verticies[] = {
         0.5f,  0.0f, 0.0f, //right
         0.0f,  0.5f, 0.0f, //top
        -0.5f,  0.0f, 0.0f, //left
         0.0f, -0.5f, 0.0f  //bottom
    };

    uint32_t indicies[] = {
        0, 1, 2,
        0, 3, 2
    };

    uint32_t vao;
    glGenVertexArrays(1, &vao);

    uint32_t vbo;
    glGenBuffers(1, &vbo);

    uint32_t ebo;
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

    uint64_t frames = 0;

    glm::mat4 transform(1.0f);

    const glm::vec3 normal(0.0f, 0.0f, 1.0f);

    GLint transform_uniform = triangleShader.get_uniform_location("transform");

    while(!glfwWindowShouldClose(window)) 
    {

        triangleShader.use();
        transform = glm::rotate(transform, glm::radians(0.1f), normal);

        glUniformMatrix4fv(transform_uniform, 1, GL_FALSE, glm::value_ptr(transform));

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        

        glfwSwapBuffers(window);
        glfwPollEvents();
        frames++;   
    }


    glfwTerminate();
    return 0;
}