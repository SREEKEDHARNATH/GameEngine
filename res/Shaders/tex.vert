#version 460 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in float aTexId;

uniform mat4 u_VP;
out vec4 fColor;
out vec2 fTexCoord;
flat out int fTexId;

void main() {
    fTexId=int(round(aTexId));
    fTexCoord=aTexCoord;
    fColor = vec4(1,1,0,1);
    gl_Position = u_VP * vec4(aPos.xy, 0, 1);
}
