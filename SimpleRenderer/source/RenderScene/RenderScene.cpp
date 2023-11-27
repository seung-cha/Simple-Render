#include "RenderScene.h"

using namespace SimpleRender;



void RenderScene::LoadDefaultScene()
{
	SceneObjects.push_back(RenderObject(""));
	ActiveObject = &SceneObjects[0];

	SceneCameras.push_back(RenderCamera());
	ActiveCamera = &SceneCameras[0];

	SceneVertexShaders.push_back(RenderShader(ShaderType::Vertex, "shaders/debug/debug.vert"));
	SceneFragmentShaders.push_back(RenderShader(ShaderType::Fragment, "shaders/debug/debug.frag"));

	SceneShaderPrograms.push_back(RenderShaderProgram());

	RenderShaderProgram* prog = &SceneShaderPrograms[0];

	prog->AttachShader(&SceneVertexShaders[0]);
	prog->AttachShader(&SceneFragmentShaders[0]);

	prog->LinkProgram();




}