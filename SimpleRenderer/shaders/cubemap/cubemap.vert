#version 330 core

layout(location = 0) in vec3 Position;


struct Transform
{
    mat4 Perspective;
    mat4 View;
    mat4 Model;

};

uniform Transform transform;

out vec3 TextureCoordinates;

void main()
{
    TextureCoordinates = Position;
    gl_Position = transform.Perspective  * mat4(mat3(transform.View)) * vec4(Position, 1.0);

}