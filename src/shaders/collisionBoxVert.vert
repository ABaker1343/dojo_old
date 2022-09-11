#version 400

layout(location=0) in vec3 aPos;

//uniform int flip;
uniform vec3 worldPos;
uniform vec3 objectScale;

uniform vec3 cameraPos;
uniform vec3 cameraScale;

uniform vec3 offset;
uniform vec3 scale;

void main () {
    vec3 renderPos;
    vec3 cameraTransform;
    
    cameraTransform.x = 1 / cameraScale.x;
    cameraTransform.y = 1 / cameraScale.y;
    cameraTransform.z = cameraScale.z;

    //renderPos = (scale * objectScale * aPos) + worldPos + (offset * objectScale);
    renderPos = (objectScale * aPos) + worldPos;
    renderPos = (renderPos * cameraTransform) - cameraPos;
    renderPos = renderPos * 2;
    renderPos = renderPos - 1.0;

    gl_Position = vec4(renderPos, 1.0);
}
