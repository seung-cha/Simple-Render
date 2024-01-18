// This file is specifically wrritten to be used with deferred rendering.

#version 330 core

layout (location = 3) out vec4 gObjectLayout;

in vec3 TextureCoordinates;
uniform samplerCube cubemap;

void main()
{
    gObjectLayout.rgba = vec4(texture(cubemap, TextureCoordinates).rgb, 0.0);

}

