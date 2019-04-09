#version 330

layout (location=0) in vec2 inVertex;
layout (location=1) in vec2 inTexture;

out vec2 texCoord;

void main() {
    gl_Position = vec4(inVertex, 0.0f, 1.0f);
    texCoord = inTexture;
}
