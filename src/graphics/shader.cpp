// shader.cpp

#include "graphics/shader.h"

#include <fstream>
#include "glad/gl.h"

#include <glm/gtc/type_ptr.hpp>

shader::shader(const std::string& vertex_path, const std::string& fragment_path) :
    program_id_{glCreateProgram()}
{
    if(program_id_ == 0)
    {
        throw std::runtime_error("Shader program failed to create.");
    }

    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

    read_shader_source(vertex_shader, vertex_path);
    read_shader_source(fragment_shader, fragment_path);

    glCompileShader(vertex_shader);
    glCompileShader(fragment_shader);

    int success;
    char info_log[512];

    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
        throw shader_compile_error(vertex_path, info_log);
    }

    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(fragment_shader, 512, NULL, info_log);
        throw shader_compile_error(fragment_path, info_log);
    } 

    glAttachShader(program_id_, vertex_shader);
    glAttachShader(program_id_, fragment_shader);

    glLinkProgram(program_id_);

    glGetProgramiv(program_id_, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(program_id_, 512, NULL, info_log);
        throw shader_link_error(info_log);
    } 

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

}

shader::~shader()
{
    glDeleteProgram(program_id_);
}


void shader::use() const
{
    glUseProgram(program_id_);
}

uint32_t shader::get_program_id() const {
    return program_id_;
}

int32_t shader::get_uniform_location(const std::string& name) const
{
    return glGetUniformLocation(program_id_, name.c_str());
}


void shader::set_uniform(const std::string& name, const glm::mat4& value) const
{
    glUniformMatrix4fv(get_uniform_location(name), 1, GL_FALSE, glm::value_ptr(value));
}

void shader::set_uniform(const std::string& name, const glm::vec4& value) const
{
    glUniform4fv(get_uniform_location(name), 1, glm::value_ptr(value));
}

void shader::set_uniform(const std::string& name, const glm::vec3& value) const
{
    glUniform3fv(get_uniform_location(name), 1, glm::value_ptr(value));
}

void shader::read_shader_source(uint32_t shader, const std::string& path) {

    //read file and put contents in source
    std::ifstream ifstream(path, std::ios::binary | std::ios::ate);
    ifstream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    size_t file_size = ifstream.tellg();
    char* source = new char[file_size + 1];
    ifstream.seekg(0);
    ifstream.read(source, file_size);
    ifstream.close();
    // make sure source string is null terminated
    source[file_size] = '\0';

    // attach source to shader id
    glShaderSource(shader, 1, &source, NULL);
    delete[] source;
}


shader_compile_error::shader_compile_error(const std::string& path, const std::string& what) :
    std::runtime_error(path + ": " + what)
{
}

shader_link_error::shader_link_error(const std::string& what) :
    std::runtime_error(what)
{
}

