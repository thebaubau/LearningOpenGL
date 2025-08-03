#version 460 core
struct Material {

//    vec3 ambient;
    sampler2D diffuse;
//    vec3 diffuse;
    sampler2D specular;
//    vec3 specular;
    sampler2D emission;
    float shininess;
};

struct Light {
  vec3 position;
  vec3 direction;
  
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;

  float constant;
  float linear;
  float quadratic;
};

out vec4 FragColor;

in vec3 Normal;  
in vec3 FragPos;
in vec2 TexCoords;
  
uniform vec3 objectColor;
uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main()
{
    float distance = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * 
                        distance + light.quadratic * (distance * distance));

    // Ambient
//    float ambientStrength = 2.0;
//    vec3 ambient  = light.ambient * material.ambient;
    vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;

    // Diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightPos = normalize(light.position - FragPos);
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(norm, lightPos), 0.0);
//    float diffPos = max(dot(norm, lightPos), 0.0);
//    vec3 diffuse = light.diffuse * (diff * material.diffuse);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;

    // Specular
//	float specularStrength = 1.0f;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectPos = reflect(-lightPos, norm);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectPos), 0.0), material.shininess);
//    float specPos = pow(max(dot(viewDir, reflectPos), 0.0), material.shininess);
    vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb;
    
    // Emission
    vec3 emission = vec3(0.0);

    if (texture(material.specular, TexCoords).r == 0.0)
    {
        emission = texture(material.emission, TexCoords).rgb;        
    }

    ambient  *= attenuation; 
    diffuse  *= attenuation;
    specular *= attenuation;

    vec3 result = ambient + diffuse + specular + emission;
    FragColor = vec4(result, 1.0);
} 