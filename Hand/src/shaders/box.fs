#version 450
out vec4 FragColor;

struct Material {
    sampler2D diffuse;
    sampler2D normal_texture;
    sampler2D specular;    
    float shininess;
}; 
struct PointLight {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
	
    float constant;
    float linear;
    float quadratic;
};
struct DirLight{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
in VS_OUT {
    vec3 FragPos;
    vec2 TexCoords;
    vec3 TangentLightDir;
    vec3 TangentLightPos;
    vec3 TangentViewPos;
    vec3 TangentFragPos;
} fs_in;

uniform Material material;
uniform PointLight pointlight;
uniform DirLight dirlight;
uniform vec3 caremaPos;

vec4 cacDirLight(DirLight light, vec3 norm)
{
        vec3 ambient = light.ambient *  texture(material.diffuse,fs_in.TexCoords).rgb;

        float diff = max(dot(norm,-fs_in.TangentLightDir),0.f);
        vec3 diffuse = diff * light.diffuse* texture(material.diffuse,fs_in.TexCoords).rgb;

        vec3 viewdir = normalize(fs_in.TangentViewPos - fs_in.TangentFragPos);
        vec3 reflectdir = normalize(reflect(fs_in.TangentLightDir,norm));
        float spec  = pow(max(dot(reflectdir,viewdir),0.f),material.shininess);
        vec3 specular = spec * light.specular *texture(material.specular,fs_in.TexCoords).rgb;
        return vec4(ambient + diffuse + specular, 1.0);
}

vec4  cacPointLight(PointLight light, vec3 norm)
{
        vec3 ambient = light.ambient *  texture(material.diffuse,fs_in.TexCoords).rgb;

        vec3 lightdir = normalize(fs_in.TangentLightPos - fs_in.TangentFragPos);
        float diff = max(dot(norm,lightdir),0.f);
        vec3 diffuse = diff * light.diffuse* texture(material.diffuse,fs_in.TexCoords).rgb;

        vec3 viewdir = normalize(fs_in.TangentViewPos - fs_in.TangentFragPos);
        vec3 reflectdir = normalize(reflect(-lightdir,norm));
        float spec  = pow(max(dot(reflectdir,viewdir),0.f),material.shininess);
        vec3 specular = spec * light.specular *texture(material.specular,fs_in.TexCoords).rgb;

        float distance = length(fs_in.TangentLightPos - fs_in.TangentFragPos);
        float attenuation  = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
        ambient  *= attenuation;  
        diffuse    *= attenuation;
        specular *= attenuation;
        return vec4(ambient + diffuse + specular, 1.0);
}

void main()
{
        vec3 normal = texture(material.normal_texture, fs_in.TexCoords).rgb;
        vec3 norm = normalize(2.0 *normal - 1.0);

        FragColor = cacPointLight(pointlight, norm);
        FragColor+= cacDirLight(dirlight,norm);

}