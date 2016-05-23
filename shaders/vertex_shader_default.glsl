#version 400

layout (location = 0) in vec3 vp; // vertex position
layout (location = 1) in vec2 tp; // texture position

out vec2 TexCoord;

// Values that stay constant for the whole mesh.
uniform mat4 MVP;

void main () {
    gl_Position = /*MVP **/ vec4 (vp, 1.0);
    //gl_Position = vec4 (vp.x, vp.y + 1.0, vp.z, 1.0);
    TexCoord = tp;
}