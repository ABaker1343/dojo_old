#version 400

out vec4 fragColor;

uniform vec3 backgroundColor;

void main () {
    fragColor = vec4(backgroundColor, 1.0);
}
