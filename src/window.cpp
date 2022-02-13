// window.cpp

#include "window.h"
#include "input.h"

#include <GLFW/glfw3.h>
#include <map>
#include <stdexcept>

/*
    My solution to not include GLFW/glfw3.h in window.h
*/
static window_id next_window_id = 0;

static std::map<GLFWwindow*, window_id> glfw_windows;

static std::map<window_id, window*> windows;


// this might be really slow idk
static window* get_window(GLFWwindow* glfw_window)
{
    return windows[glfw_windows[glfw_window]];
}

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
    if(action == GLFW_PRESS)
    {
        window* window = get_window(glfw_window);
        key_press_event e = {
            .key = key,
            .scancode = scancode,
            .mods = mods
        };
        window->publish(e);
    }
    else if(action == GLFW_REPEAT)
    {
        window* window = get_window(glfw_window);
        key_repeat_event e = {
            .key = key,
            .scancode = scancode,
            .mods = mods
        };
        window->publish(e);
    }
    else if(action == GLFW_RELEASE)
    {
        window* window = get_window(glfw_window);
        key_release_event e = {
            .key = key,
            .scancode = scancode,
            .mods = mods
        };
        window->publish(e);
    }
}

static void cursor_position_callback(GLFWwindow* glfw_window, double xpos, double ypos)
{
    window* window = get_window(glfw_window);

    cursor_move_event e = {
        .x = xpos,
        .y = ypos
    };

    window->publish(e);
}

void mouse_button_callback(GLFWwindow* glfw_window, int button, int action, int mods)
{
    if(action == GLFW_PRESS)
    {
        window* window = get_window(glfw_window);
        mouse_button_press_event e = {
            .button = button,
            .mods = mods
        };
        window->publish(e);

    }
    else if(action == GLFW_RELEASE)
    {
        window* window = get_window(glfw_window);
        mouse_button_release_event e = {
            .button = button,
            .mods = mods
        };
        window->publish(e);
    }
}

void scroll_callback(GLFWwindow* glfw_window, double xoffset, double yoffset)
{
    window* window = get_window(glfw_window);
    mouse_scroll_event e = {
        .x = xoffset,
        .y = yoffset
    };
    window->publish(e);
}
void window_close_callback(GLFWwindow* glfw_window)
{
    window* window = get_window(glfw_window);
    window_close_event e = {
        .window = *window
    };
    window->publish(e);
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

    glfwSetKeyCallback(glfw_window, key_callback);
    glfwSetCursorPosCallback(glfw_window, cursor_position_callback);
    glfwSetMouseButtonCallback(glfw_window, mouse_button_callback);
    glfwSetScrollCallback(glfw_window, scroll_callback);
    glfwSetWindowCloseCallback(glfw_window, window_close_callback);
    
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

void window::poll()
{
    glfwPollEvents();
}

void window::swap_buffers()
{
    GLFWwindow* glfw_window = get_glfw_window(this->id_);
    glfwSwapBuffers(glfw_window);
}
