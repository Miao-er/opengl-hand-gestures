#version 450
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;
layout (location = 3) in vec3 tangent;
layout (location = 4) in vec3 bitangent;

out VS_OUT {
    vec3 FragPos;
    vec2 TexCoords;
    vec3 TangentLightDir;
    vec3 TangentLightPos;
    vec3 TangentViewPos;
    vec3 TangentFragPos;
} fs_in;

uniform mat4 mvp;
uniform mat4 model;
uniform vec3 PointLightPos;
uniform vec3 cameraPos;
uniform vec3 dirLight;

void main()
{
	gl_Position = mvp* vec4(position, 1.0f);
    fs_in.FragPos = vec3(model * vec4(position, 1.0));   
    fs_in.TexCoords = texCoords;
    
    mat3 normalMatrix = transpose(inverse(mat3(model)));
    vec3 T = normalize(normalMatrix * tangent);
    vec3 B = normalize(normalMatrix * bitangent);
    vec3 N = normalize(normalMatrix * normal);    
    
    mat3 TBN = transpose(mat3(T, B, N));  
    fs_in.TangentLightPos = TBN * PointLightPos;
    fs_in.TangentViewPos  = TBN * cameraPos;
    fs_in.TangentFragPos  = TBN * fs_in.FragPos;
    fs_in.TangentLightDir = TBN * dirLight;

}