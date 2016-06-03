#version 400

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

out vec4 color;

uniform sampler2D ourTexture;
uniform vec3 lightPos;

void main () {
	// Ambient
	float ambientLight = 0.75f;
	vec3 ambient = ambientLight * vec3(1.0); // lightColor

	// Diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * vec3(1,1,0);// second vector is light color
	
    //vec4 precolor = texture(ourTexture, TexCoord);
    //color = vec4((ambient + diffuse),1) * precolor;
    vec3 precolor = vec3(0.5);
    color = vec4((ambient + diffuse) * precolor,1);
}