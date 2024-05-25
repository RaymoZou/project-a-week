#version 330 core

in vec3 fcolor;
in vec2 tex_coordinates;
out vec4 color;

uniform sampler2D ourTexture;

void main() {
    color = texture(ourTexture, tex_coordinates);
};
