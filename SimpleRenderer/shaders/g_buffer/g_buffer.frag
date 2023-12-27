#version 330 core

layout (location = 0) out vec3 gPositionLayout;
layout (location = 1) out vec3 gNormalLayout;
layout (location = 2) out vec4 gColorLayout;

struct Material
{
    sampler2D Diffuse0;
    sampler2D Specular0;

};

in vec3 gPosition;
in vec3 gNormal;
in vec2 gTexturePosition;

uniform Material material;

void main()
{
    gPositionLayout = gPosition;
    gNormalLayout = normalize(gNormal);
    gColorLayout.rgb = texture(material.Diffuse0, gTexturePosition).rgb;
    gColorLayout.a = texture(material.Specular0, gTexturePosition).r;


}