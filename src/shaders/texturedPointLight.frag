#version 400

out vec4 fragColor;

in VS_OUT {
    vec3 normal;
    vec3 fragPos;
    vec2 texPos;
} fs_in;

uniform sampler2D inTexture;
uniform samplerCube inDepthMap;

uniform vec3 lightPos;
uniform vec3 lightColor;

uniform int flip;

float ShadowCalculation(vec3 fragPos) {
    vec3 fragToLight = fragPos - lightPos;
    float closestDepth = texture(inDepthMap, fragToLight).r;
    
    closestDepth *= 50;
    float currentDepth = length(fragToLight);

    float bias = 0.05;
    float shadow = currentDepth - bias > closestDepth ? 1.0 : 0.0;

    return shadow;
}

void main() {

    float ambientStrength = 0.15;
    vec3 ambientLight = ambientStrength * lightColor;

    vec3 normal = normalize(fs_in.normal);
    vec3 lightDir = normalize(lightPos - fs_in.fragPos);

    float diffuse = max(dot(normal, lightDir), 0.0);
    vec3 diffusionLight = diffuse * lightColor;

    float shadow = ShadowCalculation(fs_in.fragPos);

    vec3 lighting = ambientLight + diffusionLight * (1 - shadow);

    vec2 texturePos = fs_in.texPos;

    if (flip != 0) {
            texturePos.x = texturePos.x * -1;
    }

    fragColor = texture(inTexture, texturePos) * vec4(lighting, 1.0);
}
