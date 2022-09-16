#version 400

layout(triangles) in;
layout(triangle_strip, max_vertices=18) out;

uniform mat4 lightProjectionTransform;
uniform mat4 lightViewTransforms[6];

out vec4 fragPos;

void main () {

    for (int face = 0; face < 6; face++) {
        gl_Layer = face; // set which face we are going to render to
        for (int i = 0; i < 3; i++) {       // for each point in a triangle
            fragPos = gl_in[i].gl_Position;
            gl_Position = lightProjectionTransform * lightViewTransforms[face] * fragPos;
            EmitVertex();
        }
        EndPrimitive();
    }

}
