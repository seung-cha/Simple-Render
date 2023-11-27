#include "RenderScene.h"
#include "RenderObject/RenderObject.h"



using namespace SimpleRender;

void RenderScene::DrawScene()
{

	for(auto& object : SceneObjects)
	{
		object->Draw();
	}
}

void RenderScene::LoadDefaultScene()
{
	SceneVertexShaders.push_back(new RenderShader(ShaderType::Vertex, "shaders/debug/debug.vert"));
	SceneFragmentShaders.push_back(new RenderShader(ShaderType::Fragment, "shaders/debug/debug.frag"));

	SceneShaderPrograms.push_back(new RenderShaderProgram());

	RenderShaderProgram* prog = SceneShaderPrograms[0];

	prog->AttachShader(SceneVertexShaders[0]);
	prog->AttachShader(SceneFragmentShaders[0]);

	prog->LinkProgram();

	SceneObjects.push_back(new RenderObject(this, SceneShaderPrograms[0], ""));
	ActiveObject = SceneObjects[0];

	SceneCameras.push_back(new RenderCamera());
	ActiveCamera = SceneCameras[0];




	
}