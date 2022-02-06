#ifndef SHADER_H
#define SHADER_H
#include "glad/gl.h"
#include <string>
#include <stdexcept>

class shader 
{
public:
    shader(const std::string& vertex_path, const std::string& fragment_path);
    ~shader();

    void use() const;

    GLuint get_program_id() const;
    GLint get_uniform_location(const std::string& name) const;

protected:

    static void read_shader_source(GLuint shader, const std::string& path);

    GLuint program_id;
};


class shader_compile_error : public std::runtime_error
{
public:
    shader_compile_error(const std::string& path, const std::string& what);

};

class shader_link_error : public std::runtime_error
{
public:
    shader_link_error(const std::string& what);
};

#endif