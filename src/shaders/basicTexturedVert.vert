#version 400

layout(location=0) in vec3 aPos;
layout(location=1) in vec2 inTexPos;
layout(location=2) in vec3 aNormal;

out vec2 texPos;

uniform int flip;
uniform mat4 objectTransform;

uniform mat4 viewTransform;

uniform mat4 projection;

out vec3 normal;
out vec3 fragPos;

void main () {


    vec4 renderPos = projection * viewTransform * objectTransform * vec4(aPos, 1.0);

    texPos = inTexPos;

    if (flip != 0) {
        texPos.x = texPos.x * -1;
        texPos.y = texPos.y;
    }

    gl_Position = renderPos;

    fragPos = vec3(objectTransform * vec4(aPos, 1.0));
    normal = aNormal;
}
