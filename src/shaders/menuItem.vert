#version 400

layout(location=0) in vec2 aPos;

uniform vec2 screenPos;

void main () {
    vec2 renderPos = (aPos * 2) - 1;
    gl_Position = vec4(renderPos, 0.0, 1.0);
}
