#version 330 core

in vec3 viewPos;
in vec3 Normal;
in vec2 TexCoord;
in vec3 LightPos;
in vec3 ourColor;
in vec3 FragPos;
in vec4 FragPosLightSpace;

out vec4 FragColor;
  
uniform vec3 specularStrength;
uniform vec3 objColor;
uniform vec3 lightColor;
uniform vec3 ambientStrength;
uniform sampler2D ourTexture;
uniform vec3 lightPosition;
uniform sampler2D depthMap;
uniform sampler2D shadowMap;
uniform sampler2D normalMap; 
uniform sampler2D diffuseTexture;
// mip mapping
vec3 rgb_normal = Normal * 0.5 + 0.5; // transforms from [-1,1] to [0,1] 

layout (std140) uniform Test
{
    vec3 ambient;
};

struct NullLight {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform NullLight NoLight;

struct DirectionalLight {
    
    vec3 direction;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
#define NR_DIR_LIGHTS 1
uniform DirectionalLight DLight[NR_DIR_LIGHTS]; 


struct PointLight{
    vec3 position;
    vec3 ambient;
    
    vec3 diffuse;
    vec3 specular;
    float constant;
    float linear;
    float quadratic;
};
#define NR_POINT_LIGHTS 4
uniform PointLight PLight[NR_POINT_LIGHTS];

struct SpotLight{
vec3 position;
vec3 direction;
float cutOff;
float outerCutOff;

float constant;
float linear; 
float quadratic;

vec3 ambient;
vec3 diffuse;
vec3 specular;

};
#define NR_SPOT_LIGHTS 4
uniform SpotLight Slight[NR_SPOT_LIGHTS];

int test = 0;

vec3 CalculateDirLight(DirectionalLight light, vec3 normal, vec3 viewDir);

vec3 CalculatePointLight(PointLight light, vec3 norm, vec3 fragPos, vec3 viewDir);

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

struct Material {
    vec3 ambient;
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
    vec3 objectColor;
};
uniform Material material;

//in VS_OUT {
//    vec3 FragPos; 
//    vec2 TexCoord;
//    mat3 TBN;
//    vec3 Normal;
//    vec4 FragPosLightSpace;
//} fs_in; 

    int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;

    float ShadowCalculation(vec4 fragPosLightSpace)
    {
        vec3 norm = normalize(Normal);
        vec3 lightDir = normalize(LightPos - FragPos);
        float bias = max(0.05 * (1.0 - dot(norm, lightDir)), 0.005);
        //float bias = 0.005;
        vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
        projCoords = projCoords * 0.5 + 0.5;
        float closestDepth = texture(shadowMap, projCoords.xy).r;
        float currentDepth = projCoords.z;
        float shadow = currentDepth - bias > closestDepth ? 1.0 : 0.0;
        if (projCoords.z > 1.0)
        shadow = 0.0;
        //float shadow = currentDepth > closestDepth ? 1.0 : 0.0;

        return shadow;
    }
    //out vec2 TexCoords;

     vec3 CalculateDirLight(DirectionalLight light, vec3 normal, vec3 viewDir)
     {
          vec3 lightDir = normalize(-light.direction);
          // diffuse shading
          float diff = max(dot(normal, lightDir), 0.0);
          // specular shading
          vec3 reflexDir = reflect(-lightDir, normal);
          float spec = pow(max(dot(viewDir, reflexDir), 0.0), material.shininess);
          // combine results
          vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoord));
          vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoord));
          vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoord));
          return (ambient + diffuse + specular);
     }

     vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
     {
        vec3 lightDir = normalize(light.position - fragPos);
        // diffuse shading
        float diff = max(dot(normal, lightDir), 0.0);
         // specular shading
         vec3 reflectDir = reflect(-lightDir, normal);
         float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
         // attenuation
         float distance = length(light.position - fragPos);
         float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
         // combine results
         vec3 ambient  = light.ambient * vec3(texture(material.diffuse, TexCoord));
         vec3 diffuse  = light.diffuse * diff * vec3(texture(material.diffuse, TexCoord));
         vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoord));
         ambient  *= attenuation;
         diffuse  *= attenuation;
         specular *= attenuation;
         return (ambient + diffuse + specular);
     }

     vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 ViewDir)
     {
        vec3 lightDir = normalize(light.position - fragPos);
        // diffuse shading
        float diff = max(dot(normal, lightDir), 0.0);
        // specular shading
        vec3 reflectDir = reflect(-lightDir, normal);
        float spec = pow(max(dot(ViewDir, reflectDir), 0.0), material.shininess);
        // attenuation
        float distance = length(light.position - fragPos);
        float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
        // spotlight intensity
        float theta = dot(lightDir, normalize(-light.direction));
        float epsilon = light.cutOff - light.outerCutOff;
        float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
        // combine results
        vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoord));
        vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoord));
        vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoord));
        ambient *= attenuation * intensity;
        diffuse *= attenuation * intensity;
        specular *= attenuation * intensity;
        return (ambient + diffuse + specular);

       
     }

void main()
{
    
    vec3 output = vec3(0.0);
//
//   output += CalculatePointLight(PLight[0], normalize(Normal), FragPos, normalize(viewPos - FragPos));
//   output += CalculateDirLight(DLight[0], normalize(Normal), normalize(viewPos - FragPos));
//   output += CalcSpotLight(Slight[0], normalize(Normal), FragPos, normalize(viewPos - FragPos));
    
    vec3 lightColor = vec3(1.0);
    float shadow = ShadowCalculation(FragPosLightSpace);
    // ambient
    vec3 ambient = NoLight.ambient * vec3(texture(material.diffuse, TexCoord));    
    //    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
     // diffuse 
    vec3 norm = normalize(Normal);
    //vec3 norm = normalize(Normal);
    //vec3 norm = normalize(Normal * 2.0 - 1.0); 
    vec3 lightDir = normalize(LightPos - FragPos);
    

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = NoLight.diffuse * diff * vec3(texture(material.diffuse, TexCoord));  
    //vec3 diffuse = diff * lightColor; 
    
    // specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos); // the viewer is always at (0,0,0) in view-space, so viewDir is (0,0,0) - Position => -Position
    vec3 halfwayDir = normalize(lightDir + viewDir);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(norm, halfwayDir), 0.0), material.shininess);
    //float spec = 0.0;
    //vec3 specular = NullLight.spec * spec * vec3(texture(material.specular, TexCoord));
    vec3 specular = NoLight.specular * spec * (vec3(1.0) - vec3(texture(material.specular, TexCoord)));
    //  vec3 specular = light.specular * spec * (vec3(1.0) - vec3(texture(material.specular, TexCoords)));
    //vec3 specular = specularStrength * spec * lightColor;
     //vec3 result = (ambient + (1.0 - shadow) * (diffuse + specular));
     vec3 result = (ambient + diffuse + specular);
    

       // have to do this differently
    // obtain normal from normal map in range [0,1]
    
    // transform normal vector to range [-1,1]
    
    //float distance = length(Light.position - FragPos);

    //float attenuation = 1.0 / (PLight.constant + PLight.linear * distance + PLight.quadratic * (distance * distance));
    //ambient  *= attenuation; 
    //diffuse  *= attenuation;
    //specular *= attenuation;   
    // rendering
    // texture(depthMap, TexCoord).r;
    //vec3 color = texture(diffuseTexture, TexCoord).rgb;
    vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular));
    //lighting += CalculatePointLight(PLight[1], norm, FragPos, viewDir);
////    
//        for(int i = 0; i < NR_POINT_LIGHTS; i++)
//        {
//         lighting =+ CalculatePointLight(PLight[i], norm, FragPos, viewDir);
//        }
//
//      
//       
//       for(int i = 0; i < NR_DIR_LIGHTS; i++)
//       {
//        lighting += CalculateDirLight(DLight[i], norm, viewDir);
//       }
////      
////
//       for(int i = 0; i < NR_SPOT_LIGHTS; i++)
//       {
//       lighting += CalcSpotLight(Slight[i], norm, FragPos, viewDir);
//       }
//       
    float depthValue = texture(depthMap, TexCoord).r;
    // texture(ourTexture, TexCoord) * 
    //FragColor = vec4(result, 1.0);  // depthvValue
    //FragColor = vec4(vec3(depthValue), 1.0) * vec4(result, 1.0);  // depthvValue
    //FragColor = vec4(vec3(lighting), 1.0);
    
    FragColor = vec4(lighting, 1.0);
} 
