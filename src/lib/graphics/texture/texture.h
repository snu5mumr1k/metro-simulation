#pragma once

#include <string>

#include <external/gl/gl_core_3_3.h>

class Texture {
public:
    Texture(const std::string &filename);
    ~Texture();

    void Activate() const;

private:
    GLuint gl_id_;
};
