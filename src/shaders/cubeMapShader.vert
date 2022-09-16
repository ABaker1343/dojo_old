#version 400

layout(location=0) in vec3 aPos;

uniform mat4 objectTransform;

void main () {
    gl_Position = objectTransform * vec4(aPos, 1.0);
}
