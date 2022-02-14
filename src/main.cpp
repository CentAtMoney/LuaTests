
#include "graphics/shader.h"
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


    application app(application_create_info);
    app.run();

    return 0;

}