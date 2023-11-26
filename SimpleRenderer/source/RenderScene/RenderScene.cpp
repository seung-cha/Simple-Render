#include "RenderScene.h"

using namespace SimpleRender;



void RenderScene::LoadDefaultScene()
{
	SceneObjects.push_back(RenderObject(""));
	ActiveObject = &SceneObjects[0];

	SceneCameras.push_back(RenderCamera());
	ActiveCamera = &SceneCameras[0];

}