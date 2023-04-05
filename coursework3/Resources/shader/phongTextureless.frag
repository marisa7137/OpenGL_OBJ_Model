#version 330 core

out vec4 fragColour;
in vec3 FragPos;
in vec2 TexCoords;
in vec3 Normal;

struct DirectionalLight {
    vec3 lightPos;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight {
    vec3 lightPos;
    vec3 lightDir;
    float cutOff;
    float outerCutOff;
  
    float constant;
    float linear;
    float quadratic;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;       
};

struct Material{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

uniform bool isUsingSpotLight;
uniform SpotLight spotLight;
uniform DirectionalLight directionalLight;
uniform Material material;
uniform vec3 camPos;

vec3 CalcDirectionalLight(DirectionalLight d_light, vec3 normal)
{
    vec3 ambient = d_light.ambient * material.ambient;
    // diffuse 
    vec3 lightDir = normalize(d_light.lightPos - FragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = d_light.diffuse * (diff * material.diffuse);
    
    // specular
    vec3 camDir = normalize(camPos - FragPos);
    //vec3 reflectDir = reflect(-lightDir, normal);  
    vec3 halfwayDir = normalize(lightDir + camDir);
    float spec = pow(max(dot(camDir, halfwayDir), 0.0), material.shininess);
    vec3 specular = d_light.specular * (spec * material.specular);  
        
    vec3 result = ambient + diffuse + specular;
    return result;
}

vec3 CalcSpotLight(SpotLight s_light, vec3 normal)
{
    vec3 lightDir = normalize(s_light.lightPos - FragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 camDir = normalize(camPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);  
    //vec3 halfwayDir = normalize(lightDir + camDir);
    float spec = pow(max(dot(camDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance = length(s_light.lightPos - FragPos);
    float attenuation = 1.0 / (s_light.constant + s_light.linear * distance + s_light.quadratic * (distance * distance));    
    // spotlight intensity
    float theta = dot(lightDir, normalize(-s_light.lightDir)); 
    float epsilon = s_light.cutOff - s_light.outerCutOff;
    float intensity = clamp((theta - s_light.outerCutOff) / epsilon, 0.0, 1.0);
    // combine results
    vec3 ambient = s_light.ambient * material.ambient;
    vec3 diffuse = s_light.diffuse * (diff * material.diffuse);
    vec3 specular = s_light.specular * (spec * material.specular);
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return (ambient + diffuse + specular);
}

void main()
{    
    vec3 norm = normalize(Normal);
    vec3 result = CalcDirectionalLight(directionalLight, norm);
    if(isUsingSpotLight){
        result += CalcSpotLight(spotLight, norm);
    }
    fragColour = vec4(result, 1.0f);
}

