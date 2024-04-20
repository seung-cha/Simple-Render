#version 330 core

layout (location = 0) out vec3 gPositionLayout;
layout (location = 1) out vec3 gNormalLayout;
layout (location = 2) out vec4 gColorLayout;
layout (location = 3) out vec4 gObjectLayout;
layout (location = 4) out vec3 gTangentLayout;
layout (location = 5) out vec3 gBiTangentLayout;
layout (location = 6) out vec3 gNormalMapLayout;

struct Material
{
    sampler2D Diffuse0;
    sampler2D Specular0;
    sampler2D Normal0;

};

in vec3 gPosition;
in vec3 gNormal;
in vec2 gTexturePosition;
in vec3 gTangent;
in vec3 gBiTangent;

in float gObject;

uniform Material material;

void main()
{
    gPositionLayout = gPosition;
    gNormalLayout = normalize(gNormal);
    gColorLayout.rgb = texture(material.Diffuse0, gTexturePosition).rgb;
    gColorLayout.a = texture(material.Specular0, gTexturePosition).r;

    gNormalMapLayout = texture(material.Normal0, gTexturePosition).rgb;

    gBiTangentLayout = gBiTangent;
    gTangentLayout = gTangent;

    gObjectLayout.a = gObject;


}