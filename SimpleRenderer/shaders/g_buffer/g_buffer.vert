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

out vec3 gPosition;
out vec3 gNormal;
out vec2 gTexturePosition;
out float gObject;      // 0.0 if a geometry exists.



uniform Transform transform;

void main()
{
    gl_Position = transform.Perspective * transform.View * transform.Model * vec4(Position, 1.0);

    vec4 worldModel = transform.Model * vec4(Position, 1.0);
    gPosition =  worldModel.xyz;




    mat3 normMat = transpose(inverse(mat3(transform.Model)));
    gNormal = normMat * Normal;


    gTexturePosition = TexturePosition;

    gObject = 1.0;
}




