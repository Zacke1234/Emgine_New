#version 330 core

in vec3 viewPos;
in vec3 Normal;
in vec2 TexCoord;
in vec3 LightPos;
in vec3 ourColor;
in vec3 FragPos;
in vec4 FragPosLightSpace;
//out mat4 view;
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

uniform int NumDirectionalLights;
uniform int NumPointLights;
uniform int NumSpotLights;



struct BasicLight {
// dir
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    // point
    
    
    vec3 position;
     float constant;
    float linear;
    float quadratic;
    // spot
    float cutOff;
    float outerCutOff;
};
uniform BasicLight baseLight;

// mip mapping
vec3 rgb_normal = Normal * 0.5 + 0.5; // transforms from [-1,1] to [0,1] 

//layout (location = 1) out BasicLight baseLight;

struct DirectionalLight {
    
    vec3 direction;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

#define NR_DIR_LIGHTS 10
uniform DirectionalLight dirLight[NR_DIR_LIGHTS];


struct PointLight{
    vec3 position;
    vec3 ambient;
    
    vec3 diffuse;
    vec3 specular;
    float constant;
    float linear;
    float quadratic;
};
#define NR_POINT_LIGHTS 10
uniform PointLight pointLight[NR_POINT_LIGHTS];


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
#define NR_SPOT_LIGHTS 10
uniform SpotLight spotLight[NR_SPOT_LIGHTS];
 

vec3 CalculateDirLight(DirectionalLight dirLight, vec3 normal, vec3 viewDir, float shadow);

vec3 CalculatePointLight(PointLight pointLight, vec3 norm, vec3 fragPos, vec3 viewDir, float shadow);

vec3 CalcSpotLight(SpotLight spotLight, vec3 normal, vec3 fragPos, vec3 viewDir, float shadow);

struct Material {
    
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
    vec3 objectColor;
};
uniform Material material;

    int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;

    float ShadowCalculation(vec4 fragPosLightSpace)
    {
        vec3 norm = normalize(Normal);
        vec3 lightDir = normalize(baseLight.direction - FragPos);
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
    float shadow = ShadowCalculation(FragPosLightSpace);

     vec3 CalculateDirLight(DirectionalLight dirLight, vec3 normal, vec3 viewDir, float shadow)
     { 
          vec3 lightDir = normalize(-dirLight.direction);
          // diffuse shading
          float diff = max(dot(normal, lightDir), 0.0);
          // specular shading
          vec3 reflexDir = reflect(-lightDir, normal);
          float spec = pow(max(dot(viewDir, reflexDir), 0.0), material.shininess);
          // combine results
          vec3 ambient = dirLight.ambient * vec3(texture(material.diffuse, TexCoord));
          vec3 diffuse = dirLight.diffuse * diff * vec3(texture(material.diffuse, TexCoord));
          vec3 specular = dirLight.specular * spec * vec3(texture(material.specular, TexCoord));
          return (ambient + (1.0 - shadow) * (diffuse + specular) * material.objectColor);
     }

     vec3 CalculatePointLight(PointLight pointLight, vec3 normal, vec3 fragPos, vec3 viewDir, float shadow)
     { 
        vec3 lightDir = normalize(pointLight.position - fragPos);
        // diffuse shading
        float diff = max(dot(normal, lightDir), 0.0);
         // specular shading
         vec3 reflectDir = reflect(-lightDir, normal);
         float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
         // attenuation
         float distance = length(pointLight.position - fragPos);
         float attenuation = 1.0 / (pointLight.constant + pointLight.linear * distance + pointLight.quadratic * (distance * distance));    
         // combine results
         vec3 ambient = pointLight.ambient * vec3(texture(material.diffuse, TexCoord));
         vec3 diffuse = pointLight.diffuse * diff * vec3(texture(material.diffuse, TexCoord));
         vec3 specular = pointLight.specular * spec * vec3(texture(material.specular, TexCoord));
         ambient *= attenuation;
         diffuse *= attenuation;
         specular *= attenuation;
         return (ambient + diffuse + specular) * ((1.0 - shadow) * material.objectColor);
         //  return (ambient + diffuse + specular);
     }

     vec3 CalcSpotLight(SpotLight spotLight, vec3 normal, vec3 fragPos, vec3 ViewDir, float shadow)
     {
         
        vec3 lightDir = normalize(spotLight.position - fragPos);
        // diffuse shading
        float diff = max(dot(normal, lightDir), 0.0);
        // specular shading
        vec3 reflectDir = reflect(-lightDir, normal);
        float spec = pow(max(dot(ViewDir, reflectDir), 0.0), material.shininess);
        // attenuation
        float distance = length(spotLight.position - fragPos);
        float attenuation = 1.0 / (spotLight.constant + spotLight.linear * distance + spotLight.quadratic * (distance * distance));
        // spotlight intensity
        float theta = dot(lightDir, normalize(-spotLight.direction));
        float epsilon = spotLight.cutOff - spotLight.outerCutOff;
        float intensity = clamp((theta - spotLight.outerCutOff) / epsilon, 0.0, 1.0);
        // combine results
        vec3 ambient = spotLight.ambient * vec3(texture(material.diffuse, TexCoord));
        vec3 diffuse = spotLight.diffuse * diff * vec3(texture(material.diffuse, TexCoord));
        vec3 specular = spotLight.specular * spec * vec3(texture(material.specular, TexCoord));
        ambient *= attenuation * intensity;
        diffuse *= attenuation * intensity;
        specular *= attenuation * intensity;
        return (ambient + (1.0 - shadow) * (diffuse + specular) * material.objectColor);

       
     }

void main()
{
    
//    switch(LightType)
//    {
//    
//    }

//    vec3 output = vec3(0.0);
////
////   output += CalculatePointLight(PLight[0], normalize(Normal), FragPos, normalize(viewPos - FragPos));
////   output += CalculateDirLight(DLight[0], normalize(Normal), normalize(viewPos - FragPos));
////   output += CalcSpotLight(Slight[0], normalize(Normal), FragPos, normalize(viewPos - FragPos));
//    
//    vec3 lightColor = vec3(1.0);
//    float shadow = ShadowCalculation(FragPosLightSpace);
//    // ambient
//    vec3 ambient = baseLight.ambient * vec3(texture(material.diffuse, TexCoord));    
//    //    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
//     // diffuse 
    vec3 norm = normalize(Normal);
//    //vec3 norm = normalize(Normal);
//    //vec3 norm = normalize(Normal * 2.0 - 1.0); 
//    vec3 lightDir = normalize(baseLight.direction - FragPos);
//    
//
//    float diff = max(dot(norm, lightDir), 0.0);
//    vec3 diffuse = baseLight.diffuse * diff * vec3(texture(material.diffuse, TexCoord));  
//    //vec3 diffuse = diff * lightColor; 
//    
//    // specular
//    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos); // the viewer is always at (0,0,0) in view-space, so viewDir is (0,0,0) - Position => -Position
//    vec3 halfwayDir = normalize(lightDir + viewDir);
//    vec3 reflectDir = reflect(-lightDir, norm);  
//    float spec = pow(max(dot(norm, halfwayDir), 0.0), material.shininess);
//    //float spec = 0.0;
//    //vec3 specular = NullLight.spec * spec * vec3(texture(material.specular, TexCoord));
//    vec3 specular = baseLight.specular * spec * (vec3(1.0) - vec3(texture(material.specular, TexCoord)));
    //  vec3 specular = light.specular * spec * (vec3(1.0) - vec3(texture(material.specular, TexCoords)));
    //vec3 specular = specularStrength * spec * lightColor;
     //vec3 result = (ambient + (1.0 - shadow) * (diffuse + specular));
     //vec3 result = (ambient + diffuse + specular);
    
     
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
    //vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular));
    vec3 lighting; //= CalculateDirLight(norm, viewDir, shadow) + CalculatePointLight(norm, FragPos, viewDir, shadow) + CalcSpotLight(norm, FragPos, viewDir, shadow);

//    lighting += CalculatePointLight(norm, FragPos, viewDir);
//    lighting += CalcSpotLight(norm, FragPos, viewDir);
////    

      
//       
       for(int i = 0; i < NumDirectionalLights; i++)
       {
       lighting += CalculateDirLight(dirLight[i], norm, viewDir, shadow);
       }

       for(int i = 0; i < NumSpotLights; i++)
       {
       lighting +=  CalcSpotLight(spotLight[i], norm, FragPos, viewDir, shadow);
       }

       for(int i = 0; i < NumPointLights; i++)
       {
       lighting +=  CalculatePointLight(pointLight[i], norm, FragPos, viewDir, shadow);
       }

//       
    float depthValue = texture(depthMap, TexCoord).r;
    // texture(ourTexture, TexCoord) * 
    //FragColor = vec4(result, 1.0);  // depthvValue
    //FragColor = vec4(vec3(depthValue), 1.0) * vec4(result, 1.0);  // depthvValue
    //FragColor = vec4(vec3(lighting), 1.0);
    
    FragColor = vec4(lighting, 1.0);
} 
