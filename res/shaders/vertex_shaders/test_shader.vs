#version 330 core

layout (location = 0) in vec3 pos;
uniform float off_x;

void main() {
    gl_Position = vec4(pos, 1.0);
    gl_Position.x += off_x;
}