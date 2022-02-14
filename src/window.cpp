// window.cpp

#include "window/window.h"
#include "input.h"
#include "glad/gl.h"

#include <iostream>

#include <map>
#include <stdexcept>

static bool glad_initialized = false;

static std::map<GLFWwindow*, window*> glfw_windows;

static window* get_window(GLFWwindow* glfw_window)
{
    return glfw_windows[glfw_window];
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

static void mouse_button_callback(GLFWwindow* glfw_window, int button, int action, int mods)
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

static void scroll_callback(GLFWwindow* glfw_window, double xoffset, double yoffset)
{
    window* window = get_window(glfw_window);
    mouse_scroll_event event = {
        .x = xoffset,
        .y = yoffset
    };
    window->publish(event);
}

static void window_close_callback(GLFWwindow* glfw_window)
{
    window* window = get_window(glfw_window);
    window_close_event event = {
        .window = window
    };
    window->publish(event);
}

static void framebuffer_size_callback(GLFWwindow* glfw_window, int width, int height)
{
    window* window = get_window(glfw_window);
    extent2d extent = {
        .width = (uint32_t) width,
        .height = (uint32_t) height
    };
    framebuffer_resize_event event = {
        .extent = extent
    };
    window->publish(event);
}

static void window_size_callback(GLFWwindow* glfw_window, int width, int height)
{
    window* window = get_window(glfw_window);
    extent2d extent = {
        .width = (uint32_t) width,
        .height = (uint32_t) height
    };
    window_resize_event event = {
        .extent = extent
    };
    window->publish(event);
}


window::window(window::create_info info)
{

    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* glfw_window = glfwCreateWindow(info.width, info.height, info.title.c_str(), NULL, NULL);

    if(glfw_window != NULL)
    {
        glfw_windows[glfw_window] = this;
        glfw_window_ = glfw_window;
    }
    else
    {
        throw std::runtime_error("GLFW window could not be created.");
    }




    glfwSetKeyCallback(glfw_window_, key_callback);
    glfwSetCursorPosCallback(glfw_window_, cursor_position_callback);
    glfwSetMouseButtonCallback(glfw_window_, mouse_button_callback);
    glfwSetScrollCallback(glfw_window_, scroll_callback);
    glfwSetWindowCloseCallback(glfw_window_, window_close_callback);
    glfwSetFramebufferSizeCallback(glfw_window_, framebuffer_size_callback);   
    glfwSetWindowSizeCallback(glfw_window_, window_size_callback);

    glfwMakeContextCurrent(glfw_window_);

    if(!glad_initialized)
    {
        gladLoadGL(glfwGetProcAddress);
        glad_initialized = true;
    }
    glViewport(0,0,info.width,info.height);

    glfwSwapInterval(1);
}


window::~window()
{
    if(glfw_window_ != NULL)
    {
        glfw_windows.erase(glfw_window_);
        glfwDestroyWindow(glfw_window_);
    }

    glfwTerminate();
}

void window::poll()
{
    glfwPollEvents();
}

void window::swap_buffers()
{
    glfwSwapBuffers(glfw_window_);
}
