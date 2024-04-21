#include "RenderScene.h"
#include "RenderObject/RenderObject.h"
#include "RenderApplication/RenderApplication.h"
#include "RenderCubemap/RenderCubemap.h"
#include "RenderDeferredRender/RenderDeferredRender.h"

#include "RenderShaderProgram/ShaderProgramData.h"

#include "imgui.h"

#include <algorithm>


using namespace SimpleRender;
using namespace std;

RenderScene::RenderScene(RenderApplication* application)
{

	this->application = application;

	objectSelectionShaderProgram = make_unique<RenderShaderProgram>();
	selectionVert = std::make_unique<RenderShader>(ShaderType::Vertex, "shaders/object_selection/selection.vert");
	selectionFrag = std::make_unique<RenderShader>(ShaderType::Fragment, "shaders/object_selection/selection.frag");


	objectSelectionShaderProgram->AttachShader(selectionVert.get());
	objectSelectionShaderProgram->AttachShader(selectionFrag.get());
	objectSelectionShaderProgram->LinkProgram();


	gbufferShaderProgram = std::make_unique<RenderShaderProgram>();
	gBufferVert = std::make_unique<RenderShader>(ShaderType::Vertex, "shaders/g_buffer/g_buffer.vert");
	gBufferFrag = std::make_unique<RenderShader>(ShaderType::Fragment, "shaders/g_buffer/g_buffer.frag");

	gbufferShaderProgram->AttachShader(gBufferVert.get());
	gbufferShaderProgram->AttachShader(gBufferFrag.get());
	gbufferShaderProgram->LinkProgram();

	//Initiate deferred render
	deferredRender = make_unique<RenderDeferredRender>(this);

	// Init cubemap
	cubemap = make_unique<RenderCubemap>();
	cubemap->SetSide(CubemapSide::Left, "imgs/left.jpg");
	cubemap->SetSide(CubemapSide::Right, "imgs/right.jpg");
	cubemap->SetSide(CubemapSide::Top, "imgs/top.jpg");
	cubemap->SetSide(CubemapSide::Bottom, "imgs/bottom.jpg");
	cubemap->SetSide(CubemapSide::Back, "imgs/back.jpg");
	cubemap->SetSide(CubemapSide::Front, "imgs/front.jpg");


}

SimpleRender::RenderScene::~RenderScene()
{

}


void RenderScene::DrawScene(RenderCamera* const& camera, const GLuint& framebuffer)
{
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for(auto& object : *SceneObjects)
	{
		object->Draw(camera);
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT);	

}

void RenderScene::DrawScene(RenderCamera* const& camera, const GLuint& framebuffer, RenderShaderProgram* const& shaderProgram)
{

	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shaderProgram->ApplyUniformVariables();

	for(auto& object : *SceneObjects)
	{
		object->Draw(camera, shaderProgram);
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT);
}


void RenderScene::DrawGBufferScene(RenderCamera* const& camera, const GLuint& framebuffer)
{
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	cubemap->Draw(camera);

	gbufferShaderProgram->ApplyUniformVariables();

	for(auto& object : *SceneObjects)
	{
		object->Draw(camera, gbufferShaderProgram.get());
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT);


}




void RenderScene::DrawIDScene(RenderCamera* const& camera, const GLuint& framebuffer)
{
	float col[4];
	glGetFloatv(GL_COLOR_CLEAR_VALUE, col);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for(auto& obj : *SceneObjects)
	{
		obj->DrawID(camera, objectSelectionShaderProgram.get());
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glClearColor(col[0], col[1], col[2], col[3]);
}

void RenderScene::LoadDefaultScene()
{
	SceneVertexShaders->push_back(std::make_unique<RenderShader>(ShaderType::Vertex, "shaders/debug/debug.vert"));
	SceneFragmentShaders->push_back(std::make_unique<RenderShader>(ShaderType::Fragment, "shaders/debug/debug.frag"));

	SceneShaderPrograms->push_back(std::make_unique<RenderShaderProgram>());

	RenderShaderProgram* prog = (*SceneShaderPrograms)[0].get();

	prog->AttachShader((*SceneVertexShaders)[0].get());
	prog->AttachShader((*SceneFragmentShaders)[0].get());

	prog->LinkProgram();

	AddObject(shaderPrograms[0].get());
	ActiveObject = objects[0].get();


}


void RenderScene::AddObject(RenderShaderProgram* const& program, const std::string& path)
{
	objects.push_back(std::make_unique<SimpleRender::RenderObject>(this, program, objects.size() + 1, path));

	std::cout << "Size of data structure: " << objects.size() << std::endl;
}


void RenderScene::DeleteObject(RenderObject* const object)
{
	if(object == nullptr)
		return;

	auto temp = object->Children;
	for(RenderObject* const& obj : temp)
	{
		DeleteObject(obj);
	}

	if(object->Parent)
	{
		// Remove a reference to this from the parent's children vector
		object->Parent->Children.erase(object);
	}

	std::cout << "Deleting: " << object->Name << std::endl;

	objects.erase(objects.begin() + object->ID - 1);
	

	// Reassign the IDs afterwads

	for(int i = 0; i < objects.size(); i++)
	{
		objects[i]->SetID(i + 1);
	}


}

void RenderScene::DeleteActiveObject()
{
	
	DeleteObject(ActiveObject);
	ActiveObject = nullptr;

}


void RenderScene::UpdateDeferredRender()
{

	auto copy = deferredRender.release();
	deferredRender = make_unique<RenderDeferredRender>(this);

	// Add back the uniform variables
	for(auto item : *copy->ShaderProgram->UniformData)
	{
		deferredRender->ShaderProgram->UniformData->push_back(item);
	}

	// Free the previous pointer
	delete(copy);

}