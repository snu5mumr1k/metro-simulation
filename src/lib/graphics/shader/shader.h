#pragma once

#include <external/gl/gl_core_3_3.h>

#include <string>
#include <unordered_map>

class Shader {
 public:
    Shader(const std::string &vertex_shader_filename, const std::string &fragment_shader_filename);
    ~Shader();

    void Activate() const;
    void SetUniform(const std::string &name, GLint value) const;

 private:
    GLint GetLocation(const std::string &name) const;

    GLuint program_;
    GLuint vertex_shader_;
    GLuint fragment_shader_;

    mutable std::unordered_map<std::string, GLint> locations_;
};
