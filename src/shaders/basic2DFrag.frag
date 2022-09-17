#version 400

in vec2 texPos;

out vec4 fragColor;

uniform sampler2D inTexture;
uniform int flip;

uniform float animationChunkSize;
uniform int animationFrame;

void main () {

    vec2 texturePos = texPos;
    texturePos.x = texturePos.x + (animationChunkSize * animationFrame);

    if (flip != 0) {
        texturePos.x = texturePos.x * -1;
    }

    fragColor = texture(inTexture, texturePos);

}
