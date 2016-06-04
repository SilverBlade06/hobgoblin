#version 400

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

out vec4 color;

uniform sampler2D ourTexture;
uniform vec3 lightPos;
uniform vec3 cameraPosition;

void main () {
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);

	// Ambient
	float ambientLight = 0.75f;
	vec3 ambient = ambientLight * vec3(1.0); // lightColor

	// Diffuse
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * vec3(1,1,0);// second vector is light color
	
	// Specular
	float specularStrength = 0.8f;
	vec3 viewDir = normalize(cameraPosition - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * vec3(1.0); //lightColor
	
    //vec4 precolor = texture(ourTexture, TexCoord);
    //color = vec4((ambient + diffuse + specular),1) * precolor;
    vec3 precolor = vec3(0.5);
    color = vec4((ambient + diffuse + specular) * precolor,1);
}