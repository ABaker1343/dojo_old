#version 400

layout(location=0) in vec3 aPos;

uniform mat4 lightViewTransform;
uniform mat4 lightProjectionTransform;
uniform mat4 objectTransform;


void main () {
    gl_Position = lightProjectionTransform * lightViewTransform * objectTransform * vec4(aPos, 1.0);
}
