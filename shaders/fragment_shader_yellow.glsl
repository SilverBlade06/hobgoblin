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

	float constant;
    float linear;
    float quadratic;
};

struct DirectionalLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
	float cutOff;

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
uniform SpotLight spotLight;

void main () {
	vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(cameraPosition - FragPos);

// Directional Light calculations

	vec3 dirLightDir = normalize(-dirLight.direction);

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
	float distance = length(pointLight.position - FragPos);
	float attenuation = 1.0f / 
	(pointLight.constant + pointLight.linear * distance + pointLight.quadratic * (distance * distance));

	vec3 lightDir = normalize(pointLight.position - FragPos);

	// Ambient
	vec3 ambient = pointLight.ambient * vec3(texture(material.diffuse, TexCoord)) * attenuation;

	// Diffuse
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = pointLight.diffuse * diff * vec3(texture(material.diffuse, TexCoord)) * attenuation;
	
	// Specular
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = pointLight.specular * spec * vec3(texture(material.specular, TexCoord)) * attenuation;

// Spotlight calculations
	vec3 spotLightDir = normalize(spotLight.position - FragPos);
	float theta = dot(spotLightDir, normalize(-spotLight.direction));

	vec3 sumAmbient;
	vec3 sumDiffuse;
	vec3 sumSpecular;
	vec3 spotAmbient;
	vec3 spotDiffuse;
	vec3 spotSpecular;

	if (theta > spotLight.cutOff) {
		// Ambient
		spotAmbient = spotLight.ambient * vec3(texture(material.diffuse, TexCoord));

		// Diffuse
		float spotDiff = max(dot(norm, spotLightDir), 0.0);
		spotDiffuse = spotLight.diffuse * spotDiff * vec3(texture(material.diffuse, TexCoord));
	
		// Specular
		vec3 spotReflectDir = reflect(-spotLightDir, norm);
		float spotSpec = pow(max(dot(viewDir, spotReflectDir), 0.0), material.shininess);
		spotSpecular = spotLight.specular * spotSpec * vec3(texture(material.specular, TexCoord));

		// Summarize
		sumAmbient = dirAmbient + ambient + spotAmbient;
		sumDiffuse = dirDiffuse + diffuse + spotDiffuse;
		sumSpecular = dirSpecular + specular + spotSpecular;
	} else {
// Summarize
	sumAmbient = dirAmbient + ambient;
	sumDiffuse = dirDiffuse + diffuse;
	sumSpecular = dirSpecular + specular;
	}
	color = vec4(sumAmbient + sumDiffuse + sumSpecular, 1);
}