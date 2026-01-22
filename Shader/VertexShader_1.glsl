#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;




out vec3 ourColor;


out vec3 FragPos;

   out vec2 TexCoord;
    out mat3 TBN;
    out vec3 Normal;
    out vec4 FragPosLightSpace;
   // out vec4 FragPosShadowSpace;
    //out mat4 view;

uniform vec3 lightPos; // we now define the uniform in the vertex shader and pass the 'view space' lightpos to the fragment shader. lightPos is currently in world space.
uniform mat4 view;
uniform mat4 transform;
uniform mat4 projection;
uniform mat4 lightSpaceMatrix;




void main()
{ 
   
    // mip map
  
   

     //mip mapping
     // obtain normal from normal map in range [0,1]
     //Normal = texture(normalMap, fs_in.TexCoord).rgb;
     // transform normal vector to range [-1,1]
     //Normal = normalize(Normal * 2.0 - 1.0); 
     

     FragPos = vec3(transform * vec4(aPos, 1.0));
    
     Normal = transpose(inverse(mat3(transform))) * aNormal;
     TexCoord = aTexCoord;
     FragPosLightSpace = lightSpaceMatrix * vec4(FragPos, 1.0);
     // lightSpaceMatrix
   
    // viewPos = vec3(view * transform); // something wrong here? This is the thing that is controlling the specular
 
     gl_Position = projection * view * transform * vec4(aPos, 1.0); 
   
   
   
    

    
}


// //Normal = transpose(inverse(mat3(transform))) * aNormal;






