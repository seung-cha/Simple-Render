#include "RenderScene.h"
#include "RenderObject/RenderObject.h"
#include "RenderApplication/RenderApplication.h"

#include "imgui.h"


using namespace SimpleRender;
using namespace std;

RenderScene::RenderScene(RenderApplication* application)
{
	// initialise a frame buffer
	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

	glGenTextures(1, &screenTexture);
	glBindTexture(GL_TEXTURE_2D, screenTexture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, application->Status->Width, application->Status->Height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, screenTexture, 0);

	GLuint renderBuffer;
	glGenRenderbuffers(1, &renderBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, application->Status->Width, application->Status->Height);

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBuffer);


	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
	{
		cout << "Frame buffer is complete" << endl << endl;
	}
	else
	{
		cout << "Frame buffer is not complete" << endl << endl;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);


	this->application = application;



	RenderShader vertShader(ShaderType::Vertex, "shaders/object_selection/selection.vert");
	RenderShader fragShader(ShaderType::Fragment, "shaders/object_selection/selection.frag");

	objectSelectionShaderProgram = RenderShaderProgram();
	objectSelectionShaderProgram.AttachShader(&vertShader);
	objectSelectionShaderProgram.AttachShader(&fragShader);
	objectSelectionShaderProgram.LinkProgram();



	RenderShader gvertShader(ShaderType::Vertex, "shaders/g_buffer/g_buffer.vert");
	RenderShader gfragShader(ShaderType::Fragment, "shaders/g_buffer/g_buffer.frag");

	gbufferShaderProgram = RenderShaderProgram();
	gbufferShaderProgram.AttachShader(&gvertShader);
	gbufferShaderProgram.AttachShader(&gfragShader);
	gbufferShaderProgram.LinkProgram();
	

}

void RenderScene::DrawScene(RenderCamera* camera, GLuint& framebuffer)
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

void RenderScene::DrawScene(RenderCamera* camera, GLuint& framebuffer, RenderShaderProgram* shaderProgram)
{
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for(auto& object : *SceneObjects)
	{
		object->Draw(camera, shaderProgram);
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT);
}


void RenderScene::DrawGBufferScene(RenderCamera* camera, GLuint& framebuffer)
{
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for(auto& object : *SceneObjects)
	{
		object->Draw(camera, &gbufferShaderProgram);
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT);
}




void RenderScene::DrawIDScene(RenderCamera* camera, GLuint& framebuffer)
{
	//Store colour value
	float col[4];
	glGetFloatv(GL_COLOR_CLEAR_VALUE, col);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for(auto& obj : *SceneObjects)
	{
		obj->DrawID(camera, &objectSelectionShaderProgram);
	}


	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClearColor(col[0], col[1], col[2], col[3]);

}

void RenderScene::LoadDefaultScene()
{
	SceneVertexShaders->push_back(new RenderShader(ShaderType::Vertex, "shaders/debug/debug.vert"));
	SceneFragmentShaders->push_back(new RenderShader(ShaderType::Fragment, "shaders/debug/debug.frag"));

	SceneShaderPrograms->push_back(new RenderShaderProgram());

	RenderShaderProgram* prog = (*SceneShaderPrograms)[0];

	prog->AttachShader((*SceneVertexShaders)[0]);
	prog->AttachShader((*SceneFragmentShaders)[0]);

	prog->LinkProgram();

	AddObject(shaderPrograms[0]);
	ActiveObject = objects[0];

	SceneCameras->push_back(new RenderCamera());
	ActiveCamera = (*SceneCameras)[0];
}


void RenderScene::AddObject(RenderShaderProgram*& program, std::string path)
{
	objects.push_back(new RenderObject(this, program, objects.size() + 1, path));

}


void RenderScene::DeleteObject(RenderObject* object)
{
	if(object == nullptr)
		return;

	object->Dispose();
	objects.erase(objects.begin() + object->ID - 1);
	
	delete object;

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