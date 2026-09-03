#version 460 core

in vec4 fColor;
in vec2 fTexCoord;
flat in int fTexId;
out vec4 color;

uniform sampler2D textures[10];

void main() {

    if (fTexId == 0) {
        color = fColor;
    } else {
        color = texture(textures[fTexId], fTexCoord);
    }
}
