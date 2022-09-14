#version 400

layout(location=0) in vec3 aPos;

//uniform int flip;
uniform mat4 objectTransform;

uniform mat4 viewTransform;

uniform mat4 projection;

uniform vec4 inColor;

out vec4 color;

void main () {

    vec4 renderPos = projection * viewTransform * objectTransform * vec4(aPos, 1.0);

    color = inColor;
    gl_Position = renderPos;
}
