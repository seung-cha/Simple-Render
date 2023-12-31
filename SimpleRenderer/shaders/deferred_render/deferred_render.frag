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

    vec3 lightPos = vec3(6.0, 3.0, 0.0);


    vec3 lightDir = normalize(lightPos - pos);
    float intensity =  max(0.0, dot(lightDir, norm));



    FragColor = vec4( vec3(diff), 1.0);


}