#version 400

out vec4 fragColor;

in vec2 texPos;

uniform sampler2D inTexture;

void main() {
    //fragColor = vec4(1.0, 1.0, 0.5, 1.0);
    fragColor = texture(inTexture, texPos);
}
