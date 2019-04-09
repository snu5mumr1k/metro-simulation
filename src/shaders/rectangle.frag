#version 330

in vec2 texCoord;

uniform sampler2D textureSampler;

out vec4 FragColor;

void main() {
    FragColor = texture(textureSampler, texCoord);
    if (FragColor.a < 0.5f) {
        discard;
    }
}
