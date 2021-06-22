#version 330 core

in vec2 tex_coord;

out vec4 FragColor;

uniform sampler2D in_tex;

void main() {
    FragColor = texture(in_tex, tex_coord);
}