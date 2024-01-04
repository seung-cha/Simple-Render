#version 330 core


out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D position;
uniform sampler2D normal;
uniform sampler2D colour;

uniform vec3 viewPos;

uniform vec3 LightPosition;

void main()
{

    // Necessary Data
    vec3 pos = texture(position, TexCoords).rgb;
    vec3 norm = texture(normal, TexCoords).rgb;
    vec3 diff = texture(colour, TexCoords).rgb;
    float specular = texture(colour, TexCoords).a;

    if(specular <= 0.0)
        specular = 1.0;

    vec3 colour = vec3(0.0);

    // Light Location
    vec3 lightPos = vec3(5.0, -10.0, 0.0);
    lightPos = LightPosition;

    // Diffuse lighting calculation
    vec3 lightDir = normalize(lightPos - pos);

    float diff_intensity =  max(0.0, dot(lightDir, norm));

    // Add diffuse colour to the final colour
    colour += diff * diff_intensity;


    vec3 viewDir = normalize(viewPos - pos);

    vec3 halfWay = normalize(lightDir + viewDir);
    vec3 reflectDir = reflect(-lightDir, norm);

   // float spec_intensity = max(0.0, dot(viewDir, reflectDir));
    
    // using half-way vector
    float spec_intensity = max(0.0, dot(halfWay, norm));
    
    spec_intensity = pow(spec_intensity, 6);

    // Add specular light to the final colour
    colour += vec3(specular) * spec_intensity;

    FragColor = vec4( colour, 1.0);
    //FragColor = vec4( diff, 1.0);
}