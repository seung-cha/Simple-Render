#version 330 core


out vec4 FragColor;

in vec2 TexCoords;

sampler2D position;
sampler2D normal;
sampler2D colour;

uniform Material material;

void main()
{
    vec3 pos = texture(position, TexCoords).rgb;
    vec3 norm = texture(normal, TexCoords).rgb;
    vec3 diff = texture(colour, TexCoords).rgb;
    float specular = texture(colour, TexCoords).a;


    FragColor = vec4(diff, 1.0);


}