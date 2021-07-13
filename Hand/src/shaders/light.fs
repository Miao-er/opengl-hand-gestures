#version 450
out vec4 FragColor;

struct Material {
    sampler2D diffuse;
    sampler2D texture;
}; 
in vec2 texcoord;
uniform Material material;
void main()
{
       FragColor = mix(texture(material.texture,texcoord),vec4(1.0),0.1);

}