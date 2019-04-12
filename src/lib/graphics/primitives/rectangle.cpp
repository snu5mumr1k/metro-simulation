#include <stdexcept>

#include <external/gl/gl_core_3_3.h>

#include <lib/graphics/shader/shader.h>

#include "rectangle.h"


void DrawRectangle(
        const std::array<float, 2> &top_left,
        const std::array<float, 2> &bottom_right,
        const Texture &texture,
        const std::array<float, 2> &texture_top_left,
        const std::array<float, 2> &texture_bottom_right) {
    static Shader shader("shaders/rectangle.vert", "shaders/rectangle.frag");
    shader.Activate();
    shader.SetUniform("textureSampler", 0);
    texture.Activate();

    float coordinates[8] = {
        top_left[0],
        bottom_right[1],
        bottom_right[0],
        bottom_right[1],
        bottom_right[0],
        top_left[1],
        top_left[0],
        top_left[1],
    };

    float texture_coordinates[8] = {
        texture_top_left[0],
        texture_bottom_right[1],
        texture_bottom_right[0],
        texture_bottom_right[1],
        texture_bottom_right[0],
        texture_top_left[1],
        texture_top_left[0],
        texture_top_left[1],
    };

    GLuint faces[6] = {0, 1, 2, 2, 3, 0};

    GLuint vao;
    GLuint vbo[2];
    GLuint ebo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(2, vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), coordinates, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), texture_coordinates, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GLuint), faces, GL_STATIC_DRAW);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glDeleteBuffers(1, &ebo);
    glDeleteBuffers(2, vbo);
    glDeleteVertexArrays(1, &vao);

    if (glGetError() != GL_NO_ERROR) {
        throw std::runtime_error("glDrawElements failed");
    }
}
