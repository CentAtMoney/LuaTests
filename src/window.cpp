// window.cpp

#include "window.h"

#include <GLFW/glfw3.h>
#include <map>
#include <stdexcept>

/*
    My solution to not include GLFW/glfw3.h in window.h
*/
static window_id next_window_id = 0;

static std::map<GLFWwindow*, window_id> glfw_windows;

static std::map<window_id, window*> windows;

static GLFWwindow* get_glfw_window(window_id id)
{
    for(auto it = glfw_windows.begin(); it != glfw_windows.end(); it++)
    {
        if(it->second == id)
        {
            return it->first;
        }
    }
    return nullptr;
}

static void key_callback(GLFWwindow* glfw_window, int key, int scancode, int action, int mods)
{
    window* window = windows[glfw_windows[glfw_window]];
    if(action == GLFW_PRESS)
    {

    }
    else if(action == GLFW_REPEAT)
    {

    }
    else if(action == GLFW_RELEASE)
    {

    }
}

window::window(window::create_info info) : 
    id_(next_window_id++)
{
    windows[this->id_] = this;

    if(glfw_windows.empty())
    {
        glfwInit();
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* glfw_window = glfwCreateWindow(info.width, info.height, info.title.c_str(), NULL, NULL);

    if(glfw_window != NULL)
    {
        glfw_windows[glfw_window] = this->id_;
    }
    else
    {
        throw std::runtime_error("GLFW window could not be created.");
    }
}


window::~window()
{
    GLFWwindow* glfw_window = get_glfw_window(this->id_);
    if(glfw_window != nullptr)
    {
        glfwDestroyWindow(glfw_window);
        glfw_windows.erase(glfw_window);
    }

    if(glfw_windows.empty())
    {
        glfwTerminate();
    }

    windows.erase(this->id_);
}
