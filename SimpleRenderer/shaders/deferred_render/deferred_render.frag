#version 330 core



/* ABSOLUTELY NECESSARY */
out vec4 FragColor;

struct rendering
{
    sampler2D Position;
    sampler2D Normal;
    sampler2D Colour;
    sampler2D Object;
    vec3 ViewPosition;

};

struct screen
{
    vec2 UV;
};

in screen Screen;
uniform rendering Rendering;
/*/////////////////////// */

void main()
{
    
    /* Necessary Data. DO NOT REMOVE UNLESS YOU ARE CERTAIN YOU DO NOT NEED THEM */
    bool isObject = texture(Rendering.Object, Screen.UV).a == 1.0;        // Does current pixel represents a pixel of a geometry?
    vec3 position = texture(Rendering.Position, Screen.UV).rgb;         // World-coordinate position of the pixel, if current pixel contributes to a geometry.
    vec3 normal = texture(Rendering.Normal, Screen.UV).rgb;             // World-coordinate normal of the pixel, if the current pixel contributes to a geometry.
    vec3 diffuse = texture(Rendering.Colour, Screen.UV).rgb;            // Diffuse colour of the pixel, if the current pixel contributes to a geometry.
    float specular = texture(Rendering.Colour, Screen.UV).a;            // Specular intensity of the pixel, if the current pixel contributes to a geometry.
    vec3 cubemap = texture(Rendering.Object, Screen.UV).rgb;            // Skybox colour. Use this to render the background when current pixel is trivial (object == false)

    /* ************************************************************************* */
  
        if(isObject)
        {
            FragColor = vec4(diffuse, 1.0);
        }
        else
        {
            FragColor = vec4(cubemap, 1.0);
        }
    
}