#version 400

layout(location=0) in vec2 aPos;
layout(location=1) in vec2 inTexPos;

uniform vec2 screenPos;

out vec2 texPos;

void main () {
    vec2 renderPos = (aPos * 2) - 1;
    texPos = inTexPos;
    gl_Position = vec4(renderPos, 0.0, 1.0);
}
