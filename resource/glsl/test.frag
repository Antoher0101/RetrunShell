#version 460 core

out vec4 FragColor;
  
in vec3 Normal;
in vec3 FragPos;  
in vec2 TexCoord;

uniform vec3 lightColor;
uniform vec3 objectColor;

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 

uniform vec3 viewPos;
uniform Material material;
uniform Light light;
uniform sampler2D Texture;
uniform float iTime;

in float test;

void main()
{
    // ambient
    vec3 ambient = light.ambient * material.ambient;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position + FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * (diff * material.diffuse);
    
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * material.specular);  
       
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0)*texture(Texture,TexCoord);
}