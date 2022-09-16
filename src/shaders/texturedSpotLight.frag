#version 400

out vec4 fragColor;

in VS_OUT {
    vec3 normal;
    vec3 fragPos;
    vec2 texPos;
    vec4 fragPosLightSpace;
} fs_in;

uniform sampler2D inTexture;
uniform sampler2D inDepthMap;

uniform vec3 lightPos;
uniform vec3 lightColor;

uniform int flip;

float ShadowCalculation(vec4 fragPosLightSpace) {
    // perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // get the depth between 0.0 and 1.0
    projCoords = projCoords * 0.5 + 0.5;

    float closestDepth = texture(inDepthMap, projCoords.xy).r;
    float currentDepth = projCoords.z;
    
    float shadow = currentDepth > closestDepth ? 1.0 : 0.0;

    return shadow;
}

void main() {

    float ambientStrength = 0.15;
    vec3 ambientLight = ambientStrength * lightColor;

    vec3 normal = normalize(fs_in.normal);
    vec3 lightDir = normalize(lightPos - fs_in.fragPos);

    float diffuse = max(dot(normal, lightDir), 0.0);
    vec3 diffusionLight = diffuse * lightColor;

    float shadow = ShadowCalculation(fs_in.fragPosLightSpace);

    vec3 lighting = ambientLight + diffusionLight * (1 - shadow);
    //vec3 lighting = (ambientLight + (1.0 - shadow) * diffuse);

    vec2 texturePos = fs_in.texPos;

    fragColor = texture(inTexture, texturePos) * vec4(lighting, 1.0);
}
