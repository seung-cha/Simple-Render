#version 330 core

out vec4 FragColour;
struct Material
{
    sampler2D Diffuse0;
    sampler2D Specular0;

};


uniform int objectID;

void main()
{
    vec3 col = vec3(objectID/255.0);
    FragColour = vec4(col, 1.0);
}