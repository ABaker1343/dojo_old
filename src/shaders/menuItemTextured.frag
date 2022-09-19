#version 400

uniform sampler2D inTexture;

in vec2 texPos;

out vec4 fragColor;

void main () {
    fragColor = texture(inTexture, texPos);
    //fragColor = vec4(texPos, 0.0, 1.0);
}
