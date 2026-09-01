#version 460 core

layout (location = 0) in vec2 aPos;

out vec4 fColor;

void main() {
    fColor = vec4(1,0,0,1);
    gl_Position = vec4(aPos.xy, 0, 1);
}
