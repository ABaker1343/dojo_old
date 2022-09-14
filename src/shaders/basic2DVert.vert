#version 400

layout(location=0) in vec3 aPos;
layout(location=1) in vec2 inTex;

out vec2 texPos;

uniform int flip;
uniform mat4 objectTransform;
uniform mat4 viewTransform;
uniform mat4 projection;

void main () {
    vec4 renderPos = projection * viewTransform * objectTransform * vec4(aPos, 1.0);

    gl_Position = renderPos;

    texPos = inTex;
}
