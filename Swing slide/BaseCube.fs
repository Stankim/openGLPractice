#version 330 core

in vec3 FragPos;  
in vec3 Normal;
uniform vec3 lightPos; 
uniform vec3 lightColor;
uniform vec3 objectColor;

out vec4 FragColor;

void main(){
     // ambient
    float ambientStrength = 0.5f;
    vec3 ambient = ambientStrength * lightColor;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
            
    vec3 result = (ambient + diffuse) * objectColor;
    FragColor = vec4(result, 1.0);
}
