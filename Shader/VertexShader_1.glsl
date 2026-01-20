#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;
//layout (location = 3) in vec2 aTexCoords;
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec3 aBitangent;  

//layout (location = 3) in vec3 aColor;



out vec3 LightPos;
out vec3 ourColor;


out vec3 FragPos;
   out vec2 TexCoord;
    out mat3 TBN;
    out vec3 Normal;
    out vec4 FragPosLightSpace;
    //out mat4 view;

uniform vec3 lightPos; // we now define the uniform in the vertex shader and pass the 'view space' lightpos to the fragment shader. lightPos is currently in world space.
uniform mat4 view;
uniform mat4 transform;
uniform mat4 projection;
uniform mat4 lightSpaceMatrix;


// mip mapping
//out VS_OUT {
//    vec3 FragPos;
//    vec2 TexCoord;
//    mat3 TBN;
//    vec3 Normal;
//    vec4 FragPosLightSpace;
//    
//} vs_out;  
     

void main()
{ 
   
    // mip map
   vec3 T = normalize(vec3(transform * vec4(aTangent,   0.0)));
   vec3 B = normalize(vec3(transform * vec4(aBitangent, 0.0)));
   vec3 N = normalize(vec3(transform * vec4(aNormal,    0.0)));
   mat3 TBN = mat3(T, B, N);

     //mip mapping
     // obtain normal from normal map in range [0,1]
     //Normal = texture(normalMap, fs_in.TexCoord).rgb;
     // transform normal vector to range [-1,1]
     Normal = normalize(Normal * 2.0 - 1.0); 
     FragPos = vec3(transform * vec4(aPos, 1.0));
     TBN = mat3(T, B, N);
     Normal = transpose(inverse(mat3(transform))) * aNormal;
     TexCoord = aTexCoord;
     FragPosLightSpace = lightSpaceMatrix * vec4(FragPos, 1.0);
     // lightSpaceMatrix
   
    // viewPos = vec3(view * transform); // something wrong here? This is the thing that is controlling the specular
 
     gl_Position = projection * view * transform * vec4(aPos, 1.0); 
   
   
   
    

    
}


// //Normal = transpose(inverse(mat3(transform))) * aNormal;






