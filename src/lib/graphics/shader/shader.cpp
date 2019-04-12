#include <fstream>
#include <stdexcept>
#include <string>

#include "shader.h"

namespace {
std::string ReadTextFile(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cant open shader file " + filename);
    }

    std::string src;
    std::string line;
    while (getline(file, line)) {
        src += line + "\n";
    }

    return src;
}

GLuint LoadShader(const std::string &filename, GLenum type) {
    GLuint id = glCreateShader(type);
    if (!id) {
        throw std::runtime_error("Failed to create OpenGL shader");
    }

    std::string src = ReadTextFile(filename);
    const char *ptr = src.c_str();
    glShaderSource(id, 1, &ptr, nullptr);
    glCompileShader(id);

    GLint compiled;
    glGetShaderiv(id, GL_COMPILE_STATUS, &compiled);
    if (!compiled) {
        GLint error_length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &error_length);
        if (!error_length) {
            throw std::runtime_error("Cant get shader compilation error length");
        }
        std::string error_body(error_length, '\0');
        glGetShaderInfoLog(id, error_length, nullptr, error_body.data());
        throw std::runtime_error(error_body);
    }

    return id;
}

GLuint LinkProgram(GLuint vertex_shader, GLuint fragment_shader) {
    GLuint id = glCreateProgram();
    if (!id) {
        throw std::runtime_error("Cant create OpenGL program");
    }

    glAttachShader(id, vertex_shader);
    glAttachShader(id, fragment_shader);

    glLinkProgram(id);

    GLint linked;
    glGetProgramiv(id, GL_LINK_STATUS, &linked);
    if (!linked) {
        GLint error_length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &error_length);
        if (!error_length) {
            throw std::runtime_error("Cant get OpenGL program linkage error length");
        }
        std::string error_body(error_length, '\0');
        glGetShaderInfoLog(id, error_length, nullptr, error_body.data());
        throw std::runtime_error(error_body);
    }

    return id;
}
}  // namespace

Shader::Shader(const std::string &vertex_shader_filename, const std::string &fragment_shader_filename):
        program_(0),
        vertex_shader_(0),
        fragment_shader_(0),
        locations_() {
    vertex_shader_ = LoadShader(vertex_shader_filename, GL_VERTEX_SHADER);
    fragment_shader_ = LoadShader(fragment_shader_filename, GL_FRAGMENT_SHADER);
    program_ = LinkProgram(vertex_shader_, fragment_shader_);
}

Shader::~Shader() {
    glDeleteShader(vertex_shader_);
    glDeleteShader(fragment_shader_);
    glDeleteProgram(program_);
}

void Shader::Activate() const {
    glUseProgram(program_);
    if (glGetError() != GL_NO_ERROR) {
        throw std::runtime_error("glUseProgram failed");
    }
}

void Shader::SetUniform(const std::string &name, GLint value) const {
    glUniform1i(GetLocation(name), value);
    if (glGetError() != GL_NO_ERROR) {
        throw std::runtime_error("glUniform1i failed for " + name);
    }
}

GLint Shader::GetLocation(const std::string &name) const {
    auto found = locations_.find(name);
    if (found == locations_.end()) {
        GLint location = glGetUniformLocation(program_, name.c_str());
        if (glGetError() != GL_NO_ERROR) {
            throw std::runtime_error("glGetUniformLocation failed for " + name);
        }
        found = locations_.insert({name, location}).first;
    }
    return found->second;
}
