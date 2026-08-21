#version 330 core
out vec4 FragColor;

in vec2 TexCoords;






void main()
{             
    //float depth = LinearizeDepth(gl_FragCoord.z) / far_plane;
    //float depthValue = texture(depthMap, TexCoords).r;
    //FragColor = vec4(vec3(LinearizeDepth(depthValue) / far_plane), 1.0); // perspective
   // FragColor = vec4(gl_FragCoord.z, 0, 0, 1); // orthographic
}