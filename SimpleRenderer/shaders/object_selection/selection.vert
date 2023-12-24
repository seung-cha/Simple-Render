#version 330 core
layout(location=0) in vec3 Position;
layout(location=1) in vec3 Normal;
layout(location=2) in vec2 TexturePosition;

struct Transform
{
    mat4 Perspective;
    mat4 View;
    mat4 Model;

};

uniform Transform transform;

void main()
{
    gl_Position =  transform.Perspective * transform.View * transform.Model * vec4(Position, 1.0);
}




