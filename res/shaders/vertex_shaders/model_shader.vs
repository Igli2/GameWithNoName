#version 330 core
#extension GL_ARB_explicit_uniform_location : enable
#extension GL_ARB_shading_language_420pack : enable

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 in_tex_coord;
layout (location = 2) in vec4 in_overlay_color;

out vec2 tex_coord;
out vec4 overlay_color;

layout (location = 0) uniform mat4 transform;

layout(std140, binding = 2) uniform camera_perspective {
    mat4 view;
    mat4 projection;
};

void main() {
    gl_Position = projection * view * transform * vec4(pos, 1.0);
  
    tex_coord = in_tex_coord;
    overlay_color = in_overlay_color;
}