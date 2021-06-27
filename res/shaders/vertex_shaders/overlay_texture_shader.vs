#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 in_tex_coord;

out vec2 tex_coord;

uniform vec2 offset;

void main() {
    gl_Position = vec4(pos, 1.0);
    gl_Position.x += offset.x;
    gl_Position.y += offset.y;
    
    tex_coord = in_tex_coord;
}