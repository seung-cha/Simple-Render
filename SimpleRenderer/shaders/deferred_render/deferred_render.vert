#version 330 core
layout(location=0) in vec3 Position;
layout(location=1) in vec2 TextureCoordinates;

struct Transform
{
    mat4 Perspective;
    mat4 View;
    mat4 Model;

};

struct screen
{
    vec2 UV;
};

out screen Screen;

uniform Transform transform;

void main()
{
    gl_Position = vec4(Position, 1.0);
    Screen.UV = TextureCoordinates;

}




