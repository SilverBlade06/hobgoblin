#version 400

in vec2 TexCoord;

out vec4 color;

uniform sampler2D ourTexture;

void main () {
    //frag_color = vec4 (1.0, 1.0, 0.0, 1.0);
    color = texture(ourTexture, TexCoord);
}