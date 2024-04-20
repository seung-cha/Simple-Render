#version 330 core



/* ABSOLUTELY NECESSARY */
out vec4 FragColor;

struct rendering
{
    sampler2D Position;
    sampler2D Normal;
    sampler2D Colour;
    sampler2D Object;
    sampler2D Tangent;
    sampler2D BiTangent;
    sampler2D NormalMap;
    vec3 ViewPosition;

};

struct screen
{
    vec2 UV;
};

in screen Screen;
uniform rendering Rendering;
/*/////////////////////// */


uniform vec3 lightPos;


void main()
{
    /* Necessary Data. DO NOT REMOVE UNLESS YOU ARE CERTAIN YOU DO NOT NEED THEM */
    bool isObject = texture(Rendering.Object, Screen.UV).a == 1.0;      // Does current pixel represents a pixel of a geometry?
    vec3 position = texture(Rendering.Position, Screen.UV).rgb;         // World-coordinate position of the pixel, if current pixel contributes to a geometry.
    vec3 normal = texture(Rendering.Normal, Screen.UV).rgb;             // World-coordinate normal of the pixel, if the current pixel contributes to a geometry.
    vec3 normalMap = texture(Rendering.NormalMap, Screen.UV).rgb;       // Normal map of the pixel, if the current pixel contributes to a geometry.
    vec3 tangent = texture(Rendering.Tangent, Screen.UV).rgb;           // Tangent space of the fragment, if the current pixel contributes to a geometry.
    vec3 bitangent = texture(Rendering.BiTangent, Screen.UV).rgb;       // Bitangent space of the fragment, if the current pixel contributes to a geometry.
    vec3 diffuse = texture(Rendering.Colour, Screen.UV).rgb;            // Diffuse colour of the pixel, if the current pixel contributes to a geometry.
    vec3 specular = vec3(texture(Rendering.Colour, Screen.UV).a);       // Specular intensity of the pixel, if the current pixel contributes to a geometry.
    vec3 cubemap = texture(Rendering.Object, Screen.UV).rgb;            // Skybox colour. Use this to render the background when current pixel is trivial (object == false)
    /* ************************************************************************* */
  
        if(isObject)
        {
            vec3 norm = normalize(normalMap * 2.0 - 1.0);
            mat3 tbn = mat3(bitangent, tangent, normal);
            norm = normalize(tbn * norm);
            vec3 color = vec3(0.0);

            vec3 ambient = 0.1 * diffuse;

            color += ambient;

           norm = normal;

            vec3 lightDir = normalize(lightPos - position);
            float intensity = max(0, dot(norm, lightDir));
            FragColor = vec4(vec3(intensity), 1.0);

            vec3 diff = diffuse * intensity;

            color += diff;

            vec3 viewDir = normalize(Rendering.ViewPosition - position);
            vec3 half = normalize(viewDir + lightDir);

            float spec = pow(max(dot(norm, half), 0.0), 32.0);
            vec3 specu = vec3(0.2) * spec;

            color += specu;

            FragColor = vec4(color, 1.0);
        }
        else
        {
            FragColor = vec4(cubemap, 1.0);
        }
    
}