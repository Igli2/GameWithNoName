#version 330 core
#extension GL_ARB_explicit_uniform_location : enable

layout (location = 0) in vec2 pos;
layout (location = 1) in vec2 in_tex_coord;
layout (location = 2) in vec4 in_overlay_color;

out vec2 tex_coord;
out vec4 overlay_color;

layout (location = 0) uniform mat4 transform;
layout (location = 1) uniform mat4 view;
layout (location = 2) uniform mat4 projection;

void main() {
    gl_Position = projection * view * transform * vec4(pos, 0.0, 1.0);
  
    tex_coord = in_tex_coord;
    overlay_color = in_overlay_color;
}