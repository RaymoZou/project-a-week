#version 330 core

layout(location = 0) in vec2 pos;
layout(location = 1) in vec3 color;
layout(location = 2) in vec2 texture_coord;

out vec3 fcolor;
out vec2 tex_coordinates;

void main() {
    gl_Position = vec4(pos, 1.0f, 1.0f);
    fcolor = color;
    tex_coordinates = texture_coord;
};
