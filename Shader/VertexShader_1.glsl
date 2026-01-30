#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;




out vec3 ourColor;
out vec3 viewPos;

    out vec3 FragPos;
    out vec2 TexCoord;
    out vec3 Normal;
    out vec4 FragPosLightSpace;
 

uniform mat4 view;
uniform mat4 transform;
uniform mat4 projection;
uniform mat4 lightSpaceMatrix;




void main()
{ 
  

     FragPos = vec3(transform * vec4(aPos, 1.0));
    
     Normal = transpose(inverse(mat3(transform))) * aNormal;
     TexCoord = aTexCoord;
     
     // lightSpaceMatrix
   
     viewPos = vec3(view * transform); 
     FragPosLightSpace = lightSpaceMatrix * vec4(FragPos, 1.0);
 // lightSpaceMatrix *
     gl_Position =  projection * view * transform * vec4(aPos, 1.0); 
   
   

}









