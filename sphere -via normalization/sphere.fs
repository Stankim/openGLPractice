#version 330 core
out vec4 FragColor;
in vec3 Normal;
in vec3 FragPos;

uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 sphereColor;
void main()
{	vec3 ambient = vec3(0.3f);
	vec3 lightDir = normalize(lightPos - FragPos);
	vec3 norm = normalize(Normal);
	float diff_angle = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = diff_angle * lightColor;
	vec3 result = ambient + diffuse;
	FragColor = vec4(result * sphereColor, 1.0f);
}
