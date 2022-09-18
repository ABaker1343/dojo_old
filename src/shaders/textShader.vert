#version 400

layout(location=0) in vec4 vertex; // vec2 position + vec2 texture

out vec2 texPos;

void main () {
    gl_Position = vec4(vertex.xy, 0.0, 1.0);
    texPos = vertex.zw;
}
