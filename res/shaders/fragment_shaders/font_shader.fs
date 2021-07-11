#version 330 core
#extension GL_ARB_explicit_uniform_location : enable

in vec2 tex_coord;

out vec4 FragColor;

uniform sampler2D in_tex;
layout (location = 3) uniform vec4 font_color;

void main() {
    FragColor = font_color * vec4(1.0, 1.0, 1.0, texture(in_tex, tex_coord).r);
}