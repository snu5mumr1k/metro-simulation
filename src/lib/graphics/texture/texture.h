#pragma once

#include <external/gl/gl_core_3_3.h>

#include <string>

class Texture {
 public:
    explicit Texture(const std::string &filename);
    ~Texture();

    void Activate() const;

 private:
    GLuint gl_id_;
};
