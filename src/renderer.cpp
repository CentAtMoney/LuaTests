#include "renderer.h"
#include "application.h"
#include "glad/gl.h"
#include <GLFW/glfw3.h>

static bool glad_initialized = false;

void renderer::notify(const std::any& object)
{
    if(!glad_initialized && object.type() == typeid(window_create_event))
    {
        gladLoadGL(glfwGetProcAddress);
        return;
    }
}


void renderer::render()
{

}