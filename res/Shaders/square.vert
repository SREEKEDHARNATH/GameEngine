#version 460 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec4 aColor;

uniform mat4 u_VP;
out vec4 fColor;

void main() {
    fColor = aColor;
    gl_Position = u_VP * vec4(aPos.xy, 0, 1);
}
