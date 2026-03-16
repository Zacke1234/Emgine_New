#version 330 core
// shadowmapping fs
out vec4 FragColor;
in vec2 TexCoords;
//

uniform float far_plane;
uniform float near_plane;

float LinearizeDepth(float depth)
{
    float z = depth * 2.0 - 1.0;
    return (2.0 * near_plane * far_plane) / (far_plane + near_plane - z * (far_plane - near_plane));
}


void main()
{          
    float depth = LinearizeDepth(gl_FragCoord.z) / far_plane;
    FragColor = vec4(vec3(depth), 1.0);
     // * vec4(vec3(gl_FragCoord.z), 1.0)
	// gl_FragDepth = gl_FragCoord.z;
     //float depthValue = texture(depthMap, TexCoords).r;
     //FragColor = vec4(vec3(LinearizeDepth(depthValue) / far_plane), 1.0); // perspective
     //FragColor = vec4(vec3(depthValue), 1.0); // orthographic
     //fragmentDepth = gl_FragCoord.z;
}