#version 450
struct PointLight {
    vec3 position;  
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
	
    float constant;
    float linear;
    float quadratic;

};
struct DirLight{
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
    in vec3 normal;
    in vec3 fragPos;
    in vec2 pass_texcoord;
        uniform PointLight pointlight;
        uniform DirLight dirlight;
		uniform vec3 caremaPos;
		uniform sampler2D u_diffuse;
        uniform sampler2D u_specular;
		out vec4 out_color;

        vec4 cacPointLight(PointLight light, vec3 norm)
        {
        vec3 ambient = light.ambient *  texture(u_diffuse,pass_texcoord).rgb;

        vec3 lightdir = normalize(light.position - fragPos);
        float diff = max(dot(norm,lightdir),0.f);
        vec3 diffuse = diff * light.diffuse* texture(u_diffuse,pass_texcoord).rgb;

        vec3 viewdir = normalize(caremaPos - fragPos);
        vec3 reflectdir = normalize(reflect(-lightdir,norm));
       float spec  = 0;//pow(max(dot(reflectdir,viewdir),0.f),100);
        vec3 specular = spec * light.specular *texture(u_specular,pass_texcoord).rgb;

        float distance = length(light.position - fragPos);
        float attenuation  = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
        ambient  *= attenuation;  
        diffuse   *=  attenuation;
        specular *= attenuation;  
        return vec4(ambient + diffuse+specular, 1.0);
        }

        vec4 cacDirLight(DirLight light, vec3 norm)
        {
        vec3 ambient = light.ambient *  texture(u_diffuse,pass_texcoord).rgb;

        float diff = max(dot(norm,-light.direction),0.f);
        vec3 diffuse = diff * light.diffuse* texture(u_diffuse,pass_texcoord).rgb;

        vec3 viewdir = normalize(caremaPos - fragPos);
        vec3 reflectdir = normalize(reflect(light.direction,norm));
        float spec  = 0;//pow(max(dot(reflectdir,viewdir),0.f),100);
        vec3 specular = spec * light.specular *texture(u_specular,pass_texcoord).rgb;
        return vec4(ambient + diffuse + specular, 1.0);
        }
		void main() 
		{
            vec3 norm = normalize(normal);
		    out_color = cacPointLight(pointlight, norm);
            out_color +=cacDirLight(dirlight,norm);
		}
