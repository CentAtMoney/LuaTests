// glfw_window.cpp

#include "window/glfw_window.h"
#include "glad/gl.h"
#include "input.h"


int glfw_window::instance_count = 0;

static bool glad_initialized = false;

static glfw_window* get_window(GLFWwindow* window)
{
    return reinterpret_cast<glfw_window*>(glfwGetWindowUserPointer(window));
}

static void key_callback(GLFWwindow* glfw_window, int key, int scancode, int action, int mods)
{
    if(action == GLFW_PRESS)
    {
        key_press_event e = {
            .key = key,
            .scancode = scancode,
            .mods = mods
        };
        get_window(glfw_window)->publish(e);
    }
    else if(action == GLFW_REPEAT)
    {
        key_repeat_event e = {
            .key = key,
            .scancode = scancode,
            .mods = mods
        };
        get_window(glfw_window)->publish(e);
    }
    else if(action == GLFW_RELEASE)
    {
        key_release_event e = {
            .key = key,
            .scancode = scancode,
            .mods = mods
        };
        get_window(glfw_window)->publish(e);
    }
}

static void cursor_position_callback(GLFWwindow* glfw_window, double xpos, double ypos)
{

    cursor_move_event e = {
        .x = xpos,
        .y = ypos
    };

    get_window(glfw_window)->publish(e);
}

static void mouse_button_callback(GLFWwindow* glfw_window, int button, int action, int mods)
{
    if(action == GLFW_PRESS)
    {
        mouse_button_press_event e = {
            .button = button,
            .mods = mods
        };
        get_window(glfw_window)->publish(e);

    }
    else if(action == GLFW_RELEASE)
    {
        mouse_button_release_event e = {
            .button = button,
            .mods = mods
        };
        get_window(glfw_window)->publish(e);
    }
}

static void scroll_callback(GLFWwindow* glfw_window, double xoffset, double yoffset)
{
    mouse_scroll_event e = {
        .x = xoffset,
        .y = yoffset
    };
    get_window(glfw_window)->publish(e);
}

static void window_close_callback(GLFWwindow* glfw_window)
{
    window_t* window = get_window(glfw_window);
    window_close_event e = {
        .window = window
    };
    window->publish(e);
}

static void framebuffer_size_callback(GLFWwindow* glfw_window, int width, int height)
{
    extent2d extent = {
        .width = (uint32_t) width,
        .height = (uint32_t) height
    };
    framebuffer_resize_event e = {
        .extent = extent
    };
    get_window(glfw_window)->publish(e);
}

static void window_size_callback(GLFWwindow* glfw_window, int width, int height)
{
    extent2d extent = {
        .width = (uint32_t) width,
        .height = (uint32_t) height
    };
    window_resize_event e = {
        .extent = extent
    };
    get_window(glfw_window)->publish(e);
}

glfw_window::glfw_window(glfw_window::create_info info)
{
    if(glfw_window::instance_count++ == 0)
    {
        glfwInit();
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    this->glfw_window_ = glfwCreateWindow(info.width, info.height, info.title.c_str(), NULL, NULL);

    if(this->glfw_window_ == NULL)
    {
        throw std::runtime_error("GLFW window could not be created.");
    }

    glfwSetWindowUserPointer(this->glfw_window_, this);

    glfwSetKeyCallback(this->glfw_window_, key_callback);
    glfwSetCursorPosCallback(this->glfw_window_, cursor_position_callback);
    glfwSetMouseButtonCallback(this->glfw_window_, mouse_button_callback);
    glfwSetScrollCallback(this->glfw_window_, scroll_callback);
    glfwSetWindowCloseCallback(this->glfw_window_, window_close_callback);
    glfwSetFramebufferSizeCallback(this->glfw_window_, framebuffer_size_callback);   
    glfwSetWindowSizeCallback(this->glfw_window_, window_size_callback);

    glfwMakeContextCurrent(glfw_window_);

    if(!glad_initialized)
    {
        gladLoadGL(glfwGetProcAddress);
        glad_initialized = true;
    }
    glViewport(0, 0, info.width, info.height);

    glfwSwapInterval(1);
}

glfw_window::~glfw_window()
{
    if(this->glfw_window_ != NULL)
    {
        glfwDestroyWindow(this->glfw_window_);
    }

    if(--glfw_window::instance_count == 0)
    {
        glfwTerminate();
    }
}

extent2d glfw_window::get_framebuffer_extent()
{
    int width, height;
    glfwGetFramebufferSize(this->glfw_window_, &width, &height);
    extent2d extent = {
        .width = (uint32_t) width,
        .height = (uint32_t) height
    };
    return extent;
}

extent2d glfw_window::get_window_extent()
{
    int width, height;
    glfwGetWindowSize(this->glfw_window_, &width, &height);
    extent2d extent = {
        .width = (uint32_t) width,
        .height = (uint32_t) height
    };
    return extent;
}

void glfw_window::poll()
{
    glfwPollEvents();
}

void glfw_window::swap_buffers()
{
    glfwSwapBuffers(this->glfw_window_);
}

void glfw_window::disable_cursor()
{
    glfwSetInputMode(this->glfw_window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);    
}

void glfw_window::enable_cursor()
{
    glfwSetInputMode(this->glfw_window_, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}
