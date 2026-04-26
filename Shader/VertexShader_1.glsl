#version 430 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec3 aBitangent;

out vec3 ourColor;
out vec3 viewPos;
out vec3 FragPos;
out vec2 TexCoord;
out vec3 Normal;
out vec4 FragPosLightSpace;
out mat3 TBN;

uniform mat4 view;
uniform mat4 transform;
uniform mat4 projection;
uniform mat4 lightSpaceMatrix;

uniform bool reverse_normals;

void main()
{ 
     // normal mapping
     vec3 T = normalize(vec3(transform * vec4(aTangent, 0.0)));
     vec3 B = normalize(vec3(transform * vec4(aBitangent, 0.0)));
     vec3 N = normalize(vec3(transform * vec4(aNormal, 0.0)));
     TBN = mat3(T,B,N);


    // TBN = transpose(mat3(T,B,N);

     FragPos = vec3(transform * vec4(aPos, 1.0));
    
//     if(reverse_normals)
//     Normal = transpose(inverse(mat3(transform))) * (-1.0 * aNormal);
//     else
     Normal = transpose(inverse(mat3(transform))) * aNormal;

     TexCoord = aTexCoord;
  
     viewPos = vec3(view * transform); 
     FragPosLightSpace = lightSpaceMatrix * vec4(FragPos, 1.0);

     gl_Position =  projection * view * transform * vec4(aPos, 1.0);    
     
}









