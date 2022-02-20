#ifndef SHADER_H
#define SHADER_H
#include <string>
#include <stdexcept>
#include <cstdint>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

class shader 
{
public:
    shader(const std::string& vertex_path, const std::string& fragment_path);
    ~shader();

    void use() const;

    uint32_t get_program_id() const;
    int32_t get_uniform_location(const std::string& name) const;

    void set_uniform(const std::string& name, const glm::mat4& value) const;
    void set_uniform(const std::string& name, const glm::vec4& value) const;
    void set_uniform(const std::string& name, const glm::vec3& value) const;

protected:

    static void read_shader_source(uint32_t shader, const std::string& path);

    uint32_t program_id_;
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