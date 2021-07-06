#version 330 core
#extension GL_ARB_explicit_uniform_location : enable

layout (location = 0) in vec2 pos;
layout (location = 1) in vec2 in_tex_coord;

out vec2 tex_coord;

layout (location = 0) uniform vec2 window_bounds;
layout (location = 1) uniform vec3 offset;

void main() {
    gl_Position = vec4(0.0, 0.0, 0.0, 1.0);
    gl_Position.x = (pos.x + offset.x) / window_bounds.x * 2 - 1;
    gl_Position.y = 1 - (pos.y + offset.y) / window_bounds.y * 2;
    
    tex_coord = in_tex_coord;
}