#version 330 core


out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D position;
uniform sampler2D normal;
uniform sampler2D colour;


void main()
{
    vec3 pos = texture(position, TexCoords).rgb;
    vec3 norm = texture(normal, TexCoords).rgb;
    vec3 diff = texture(colour, TexCoords).rgb;
    float specular = texture(colour, TexCoords).a;


    FragColor = vec4(norm, 1.0);


}