#ifndef SHADER_H
#define SHADER_H
#include "glad/gl.h"
#include <string>
#include <stdexcept>

class Shader 
{
public:
    Shader(std::string vertexPath, std::string fragmentPath);
    ~Shader();

    void use();

    GLuint getProgramId() const;

protected:

    void read_shader_source(GLuint shader, std::string path);

    GLuint programId;
};


class shader_compile_error : public std::runtime_error
{
public:
    shader_compile_error(std::string path, std::string what);

};

class shader_link_error : public std::runtime_error
{
public:
    shader_link_error(std::string what);
};

#endif