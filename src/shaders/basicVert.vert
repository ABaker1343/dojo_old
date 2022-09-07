#version 400

layout(location=0) in vec3 aPos;
layout(location=1) in vec2 inTexPos;

out vec2 texPos;

uniform int flip;
uniform vec3 worldPos;
uniform vec3 objectScale;

uniform vec3 cameraPos;
uniform vec3 cameraScale;

void main () {
    vec3 renderPos;
    vec3 cameraTransform;
    
    cameraTransform.x = 1 / cameraScale.x;
    cameraTransform.y = 1 / cameraScale.y;
    cameraTransform.z = cameraScale.z;

    renderPos = (objectScale * aPos) + worldPos;
    renderPos = (renderPos * cameraTransform) - cameraPos;

    if (flip != 0) {
        texPos.x = inTexPos.x * -1;
        texPos.y = inTexPos.y;
    } else {
        texPos = inTexPos;
    }

    gl_Position = vec4(renderPos, 1.0);
    texPos = inTexPos;
}
