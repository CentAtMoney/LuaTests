#include "shader.h"

#include <fstream>

Shader::Shader(std::string vertexPath, std::string fragmentPath) :
    programId{glCreateProgram()}
{
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    read_shader_source(vertexShader, vertexPath);
    read_shader_source(fragmentShader, fragmentPath);

    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);

    int success;
    char infoLog[512];

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        throw shader_compile_error(vertexPath, infoLog);
    }

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        throw shader_compile_error(fragmentPath, infoLog);
    } 

    glAttachShader(programId, vertexShader);
    glAttachShader(programId, fragmentShader);

    glLinkProgram(programId);

    glGetProgramiv(programId, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(programId, 512, NULL, infoLog);
        throw shader_link_error(infoLog);
    } 

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

}

Shader::~Shader()
{
    glDeleteProgram(programId);
}


void Shader::use() 
{
    glUseProgram(programId);
}

void Shader::read_shader_source(GLuint shader, std::string path) {

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

GLuint Shader::getProgramId() const {
    return programId;
}

shader_compile_error::shader_compile_error(std::string path, std::string what) :
    std::runtime_error(path + ": " + what)
{
}

shader_link_error::shader_link_error(std::string what) :
    std::runtime_error(what)
{
}

