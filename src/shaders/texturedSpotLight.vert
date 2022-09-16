#version 400

layout(location=0) in vec3 aPos;
layout(location=1) in vec2 inTexPos;
layout(location=2) in vec3 aNormal;

uniform int flip;

uniform mat4 objectTransform;
uniform mat4 viewTransform;
uniform mat4 projection;

uniform mat4 lightViewTransform;
uniform mat4 lightProjectionTransform;

out VS_OUT {
    vec3 normal;
    vec3 fragPos;
    vec2 texPos;
    vec4 fragPosLightSpace;
} vs_out;

void main () {


    vec4 renderPos = projection * viewTransform * objectTransform * vec4(aPos, 1.0);

    vs_out.texPos = inTexPos;

    gl_Position = renderPos;

    vs_out.fragPos = vec3(objectTransform * vec4(aPos, 1.0));
    vs_out.fragPosLightSpace = lightProjectionTransform * lightViewTransform * objectTransform * vec4(aPos, 1.0);

    vs_out.normal = mat3(transpose(inverse(objectTransform))) * aNormal;
    //normal = aNormal;
}
