#version 400

uniform vec3 color;
uniform vec3 lightColor;
uniform vec3 lightPos;

in vec3 normal;
in vec3 fragPos;

out vec4 fragColor;

void main () {
    
    float ambientStrength = 0.1;
    ambientLighting = ambientStrength * lightColor;


    // get the direction of the normal
    // and the direction of the light

    vec3 norm = normalize(normal);
    lightDir = normalize(lightPos - fragPos);
    
    // get the strength of the light
    // then take thex maximum of that or 0 so we dont have negative light

    float diffusion = max(dot(norm, lightDir), 0.0);

    vec3 result = (ambientLighting + diffusion) * objectColor;

    fragColor = vec3(result, 1.0);
}
