#version 400

layout(location=0) in vec3 aPos;
layout(location=2) in vec3 aNormal;

//uniform int flip;
uniform mat4 objectTransform;

uniform mat4 viewTransform;

uniform mat4 projection;

out vec3 normal;
out vec3 fragPos;

void main () {

    vec4 renderPos = projection * viewTransform * objectTransform * vec4(aPos, 1.0);

    gl_Position = renderPos;

    // take the world pos of the fragment so that it can be used
    // for lighting
    fragPos = (model * vec4(aPos, 1.0));

    normal = aNormal;
}
