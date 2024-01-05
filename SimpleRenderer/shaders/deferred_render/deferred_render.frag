#version 330 core

out vec4 FragColor;



struct rendering
{
    sampler2D Position;
    sampler2D Normal;
    sampler2D Colour;
    vec3 ViewPosition;

};

struct screen
{
    vec2 UV;
};

in screen Screen;
uniform rendering Rendering;


void main()
{
    
    /* Necessary Data. DO NOT REMOVE UNLESS YOU ARE CERTAIN YOU DO NOT NEED THEM */
    vec3 pos = texture(Rendering.Position, Screen.UV).rgb;
    vec3 norm = texture(Rendering.Normal, Screen.UV).rgb;
    vec3 diff = texture(Rendering.Colour, Screen.UV).rgb;
    float specular = texture(Rendering.Colour, Screen.UV).a;
    /* ************************************************************************* */

    FragColor = vec4(diff, 1.0);
}