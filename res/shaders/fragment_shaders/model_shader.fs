#version 330 core
#extension GL_ARB_explicit_uniform_location : enable

in vec2 tex_coord;
in vec4 overlay_color;

out vec4 FragColor;

uniform sampler2D in_tex;
layout (location = 4) uniform bool use_texture;
layout (location = 5) uniform bool use_color;

void main() {

    if(use_color) {
        FragColor = overlay_color;
    } else {
        FragColor = vec4(1.0);
    }
    if(use_texture) FragColor *= texture(in_tex, tex_coord);
}