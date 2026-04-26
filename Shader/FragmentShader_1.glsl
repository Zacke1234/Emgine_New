#version 430 core

uniform vec3 viewPos;

in vec3 ourColor;

layout (location = 3) uniform sampler2D shadowMapTex;

out vec4 FragColor;

uniform sampler2D ourTexture;
uniform sampler2D depthMap;
uniform samplerCube depthCubeMap;
uniform sampler2D shadowMap;
uniform sampler2D normalMap; 

uniform samplerCube cubemap; // cubemap texture sampler
uniform int NumDirectionalLights;
uniform int NumPointLights;
uniform int NumSpotLights;
uniform bool LightSwitch;

in vec3 FragPos;
in vec2 TexCoord;
in vec3 Normal;
in vec4 FragPosLightSpace;
in mat3 TBN;

in vec3 TangentLightPos;
in vec3 TangentViewPos;
in vec3 TangentFragPos;

vec3 rgb_normal = Normal * 0.5 + 0.5;

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
 
vec3 gridSamplingDisk[20] = vec3[]
(
   vec3(1, 1,  1), vec3( 1, -1,  1), vec3(-1, -1,  1), vec3(-1, 1,  1), 
   vec3(1, 1, -1), vec3( 1, -1, -1), vec3(-1, -1, -1), vec3(-1, 1, -1),
   vec3(1, 1,  0), vec3( 1, -1,  0), vec3(-1, -1,  0), vec3(-1, 1,  0),
   vec3(1, 0,  1), vec3(-1,  0,  1), vec3( 1,  0, -1), vec3(-1, 0, -1),
   vec3(0, 1,  1), vec3( 0, -1,  1), vec3( 0, -1, -1), vec3( 0, 1, -1)
);

vec3 CalculateDirLight(DirectionalLight dirLight, vec3 viewDir, float shadow);

vec3 CalculatePointLight(PointLight pointLight, vec3 fragPos, vec3 viewDir, float shadow);

vec3 CalcSpotLight(SpotLight spotLight, vec3 fragPos, vec3 viewDir, float shadow);

struct Material {
    
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
    vec3 objectColor;
};

uniform Material material;

    int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;

    float PointShadowCalculation(vec3 fragposLightspace, vec3 lightpos)
    {

    vec3 fragToLight = FragPos - lightpos;

    float currentDepth = length(fragToLight);

    float bias = 0.15;
    float shadow = 0;
    int samples = 20;

    float viewDistance = length(viewPos - FragPos);
    float diskRadius = (1.0 + (viewDistance / 25.0)) / 25.0;

    for(int i = 0; i < samples; ++i)
    {
        float closestDepth = texture(depthCubeMap, fragToLight + gridSamplingDisk[i] * diskRadius).r;
        closestDepth *= 25.0;
        if(currentDepth - bias > closestDepth)
        shadow += 1.0;
    }
    shadow /= float(samples);

        return shadow;
    }

   

    float ShadowCalculation(vec4 fragPosLightSpace, vec3 lightPos)
    {
        
       // peform perspective divide
        vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
        // transform to [0,1] range
        projCoords = projCoords * 0.5 + 0.5;
        // get closest depth from light's perspective (using [0,1] range frogposlight as coords)
        float closestDepth = texture(shadowMap, projCoords.xy).r;
        // just get the depth of current fragment from lights perspective
        float currentDepth = projCoords.z;

        vec3 normal = normalize(Normal);
        //vec3 lightDir = normalize(lightPos - FragPos);

        float bias = max(0.05 * (1.0 - dot(normal, lightPos)), 0.005);
        // check whetever current frag pos is in shadow
        //float shadow = currentDepth - bias > closestDepth ? 1.0 : 0.0;
        // PCF
        float shadow = 0.0;
        vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
        for(int x = -1; x <= 1; ++x)
        {
            for (int y = -1; y<=1; ++y)
            {
                float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r;
                shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;
            }

            
        }
        
        shadow /= 9.0;  

        if (projCoords.z > 1.0)
            shadow = 0.0;
            

        return shadow;
    }
   
    
     vec3 CalculateDirLight(DirectionalLight dirLight, vec3 viewDir)
     {  
         
         
          vec3 norm = normalize(Normal);

          float shadow = ShadowCalculation(FragPosLightSpace, dirLight.direction); // do i need multiple different fragPosLights? for each light type? to properly load shadows
          vec3 lightDir = normalize(-dirLight.direction);
          // diffuse shading
          float diff = max(dot(norm, lightDir), 0.0);
          // specular shading
          vec3 reflexDir = reflect(-lightDir, norm);
          float spec = pow(max(dot(viewDir, reflexDir), 0.0), material.shininess);
          // combine results
          vec3 ambient = dirLight.ambient * vec3(texture(material.diffuse, TexCoord));
          vec3 diffuse = dirLight.diffuse * diff * vec3(texture(material.diffuse, TexCoord));
          vec3 specular = dirLight.specular * spec * vec3(texture(material.specular, TexCoord));
          return (ambient + (1.0 - shadow) * (diffuse + specular)) * material.objectColor;
     }

     vec3 CalculatePointLight(PointLight pointLight, vec3 fragPos, vec3 viewDir)
     { 
         float shadow = ShadowCalculation(FragPosLightSpace, pointLight.position);

         vec3 norm = normalize(Normal);
       
         vec3 lightDir = normalize(pointLight.position - fragPos);
         // diffuse shading
         float diff = max(dot(norm, lightDir), 0.0);
         // specular shading
         vec3 reflectDir = reflect(-lightDir, norm);
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
        
         return (ambient + (1.0 - shadow) * (diffuse  + specular)) * material.objectColor; 
         
     }

     vec3 CalcSpotLight(SpotLight spotLight, vec3 fragPos, vec3 ViewDir)
     {
        vec3 norm = normalize(Normal);

        float shadow = ShadowCalculation(FragPosLightSpace, spotLight.position);
        vec3 lightDir = normalize(spotLight.position - fragPos);
        // diffuse shading
        float diff = max(dot(norm, lightDir), 0.0);
        // specular shading
        vec3 reflectDir = reflect(-lightDir, norm);
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

         return (ambient + (1.0 - shadow) * (diffuse  + specular)) * material.objectColor;
     }

   

void main()
{
    vec3 viewDir = normalize(viewPos - FragPos); // the viewer is always at (0,0,0) in view-space, so viewDir is (0,0,0) - Position => -Position
   
    vec3 lighting = vec3(0);
          
    for(int i = 0; i < NumDirectionalLights; i++)
    {
        lighting += CalculateDirLight(dirLight[i], viewDir);
    }    

    for(int i = 0; i < NumSpotLights; i++)
    {
        lighting +=  CalcSpotLight(spotLight[i], FragPos, viewDir);
    }

    for(int i = 0; i < NumPointLights; i++)
    {
        lighting +=  CalculatePointLight(pointLight[i], FragPos, viewDir);
    }
       
    FragColor = vec4(lighting, 1.0); 

} 
