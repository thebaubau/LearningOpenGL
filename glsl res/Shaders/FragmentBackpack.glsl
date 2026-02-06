#version 460 core

out vec4 FragColor;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

uniform sampler2D diffuse1;
uniform sampler2D specular1;
uniform sampler2D normal1;
uniform sampler2D roughness1;
uniform sampler2D ao1;

uniform vec3 viewPos;
uniform vec3 lightPos;
uniform vec3 lightColor;

void main()
{    
    // Sample all textures
    vec3 albedo = texture(diffuse1, TexCoords).rgb;
    vec3 specularMap = texture(specular1, TexCoords).rgb;
    float roughness = texture(roughness1, TexCoords).r;
    float ao = texture(ao1, TexCoords).r;
    
    // Normal mapping (simplified - use Normal as-is for now)
    vec3 norm = normalize(Normal);
    
    // Lighting calculations
    vec3 lightDir = normalize(lightPos - FragPos);
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    
    // Ambient
    vec3 ambient = 0.3 * albedo * ao; // AO affects ambient
    
    // Diffuse
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * albedo * lightColor;
    
    // Specular (roughness controls shininess)
    float shininess = (1.0 - roughness) * 256.0; // Convert roughness to shininess
    float spec = pow(max(dot(norm, halfwayDir), 0.0), shininess);
    vec3 specular = spec * specularMap * lightColor;
    
    // Combine all components
    vec3 result = ambient + diffuse + specular;
    
    FragColor = vec4(result, 1.0);
}