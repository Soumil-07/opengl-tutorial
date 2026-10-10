#version 330 core

in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;  

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;
  
void main()
{
    float ambientStrength = 0.1f;
    vec3 ambientLight = lightColor * ambientStrength;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(lightDir, norm), 0.0);
    vec3 diffuseLight = lightColor * diff;

    float specularStrength = 0.5f;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(reflectDir, viewDir), 0.0f), 32);
    vec3 specular = spec * specularStrength * lightColor;

    FragColor = vec4(objectColor * (ambientLight + diffuseLight + specular), 1.0f);
}
