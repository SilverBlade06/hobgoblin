#version 400

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct DirectionalLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

out vec4 color;

uniform vec3 cameraPosition;
uniform Material material;
uniform Light pointLight;
uniform DirectionalLight dirLight;

void main () {
	vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(cameraPosition - FragPos);

// Directional Light calculations

	//vec3 dirLightDir = normalize(pointLight.position - FragPos);
	vec3 dirLightDir = normalize(-dirLight.direction); // TODO

	// Ambient
	vec3 dirAmbient = dirLight.ambient * vec3(texture(material.diffuse, TexCoord));

	// Diffuse
	float dirDiff = max(dot(norm, dirLightDir), 0.0);
	vec3 dirDiffuse = dirLight.diffuse * dirDiff * vec3(texture(material.diffuse, TexCoord));
	
	// Specular
	vec3 dirReflectDir = reflect(-dirLightDir, norm);
	float dirSpec = pow(max(dot(viewDir, dirReflectDir), 0.0), material.shininess);
	vec3 dirSpecular = dirLight.specular * dirSpec * vec3(texture(material.specular, TexCoord));

// Point Light calculations

	vec3 lightDir = normalize(pointLight.position - FragPos);
	//vec3 lightDir = normalize(-dirLight.direction); // TODO

	// Ambient
	vec3 ambient = pointLight.ambient * vec3(texture(material.diffuse, TexCoord));

	// Diffuse
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = pointLight.diffuse * diff * vec3(texture(material.diffuse, TexCoord));
	
	// Specular
	//vec3 viewDir = normalize(cameraPosition - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = pointLight.specular * spec * vec3(texture(material.specular, TexCoord));

// Summarize
	vec3 sumAmbient = dirAmbient + ambient;
	vec3 sumDiffuse = dirDiffuse + diffuse;
	vec3 sumSpecular = dirSpecular + specular;
	color = vec4(sumAmbient + sumDiffuse + sumSpecular, 1);
}