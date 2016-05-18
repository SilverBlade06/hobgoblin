#version 400

in vec2 TexCoord;

out vec4 frag_colour;

uniform sampler2D ourTexture;

void main () {
    //frag_colour = vec4 (0.0, 1.0, 0.0, 1.0);
    frag_color = texture(ourTexture, TexCoord);
}