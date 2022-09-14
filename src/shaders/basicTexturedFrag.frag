#version 400

out vec4 fragColor;

in vec2 texPos;
in vec3 normal;
in vec3 fragPos;

uniform sampler2D inTexture;
uniform vec3 lightPos;
uniform vec3 lightColor;

void main() {

    float ambientStrength = 0.4;
    vec3 ambientLight = ambientStrength * lightColor;

    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - fragPos);

    float diffusionLight = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diffusionLight * lightColor;

    vec3 lighting = ambientLight + diffusionLight;
    vec4 lightingToApply = vec4 (lighting, 1.0);

    //fragColor = vec4(1.0, 1.0, 0.5, 1.0);
    fragColor = texture(inTexture, texPos) * lightingToApply;
}
