#version 400

layout (location = 0) in vec3 vertexPosition; // vertex position
layout (location = 1) in vec2 texturePosition; // texture position
layout (location = 2) in vec3 normal; // normal vector

out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;

// Values that stay constant for the whole mesh.
uniform mat4 MVP;
uniform mat4 Model;
uniform mat4 ModelTransformed;

void main () {
    gl_Position = MVP * vec4 (vertexPosition, 1.0);
    TexCoord = texturePosition;
    FragPos = vec3(Model * vec4(vertexPosition, 1.0f));
    Normal = mat3(ModelTransformed) * normal;
}