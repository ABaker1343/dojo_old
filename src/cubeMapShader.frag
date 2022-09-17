#version 400

in vec4 fragPos;

uniform vec3 lightPos;
uniform float far_plane;

void main () {
    float distance = length(fragPos.xyz - lightPos);

    float mappedDistance = distance / farPlane;

    gl_FragDepth = mappedDistance;
}
