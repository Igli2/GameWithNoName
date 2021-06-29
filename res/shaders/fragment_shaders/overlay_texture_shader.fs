#version 330 core

in vec2 tex_coord;
in vec4 overlay_color;

out vec4 FragColor;

uniform sampler2D in_tex;
uniform bool has_texture;
uniform bool use_color;

void main() {

    if(use_color) {
        FragColor = overlay_color;
    } else {
        FragColor = vec4(1.0);
    }
    if(has_texture) FragColor *= texture(in_tex, tex_coord);
}