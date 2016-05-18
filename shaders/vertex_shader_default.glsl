#version 400

layout (location = 0) in vec3 vp; // vertex position
layout (location = 1) in vec2 tp; // texture position

//out vec3 ourColor;
out vec2 TexCoord;

void main () {
    gl_Position = vec4 (vp, 1.0);
    //gl_Position = vec4 (vp.x, vp.y + 1.0, vp.z, 1.0);
    //ourColor = color;
    TexCoord = tp;
}