#version 400

out vec4 fragColor;

in vec2 texPos;
in vec3 normal;
in vec3 fragPos;

uniform sampler2D inTexture;
uniform vec3 lightPos;
uniform vec3 lightColor;

void main() {

    float ambientStrength = 0.15;
    vec3 ambientLight = ambientStrength * lightColor;

    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - fragPos);

    float diffuse = max(dot(norm, lightDir), 0.0);
    vec3 diffusionLight = diffuse * lightColor;

    vec3 lighting = ambientLight + diffusionLight;

    fragColor = texture(inTexture, texPos) * vec4(lighting, 1.0);
}
