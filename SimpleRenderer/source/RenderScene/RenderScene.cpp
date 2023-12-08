#include "RenderScene.h"
#include "RenderObject/RenderObject.h"

#include "imgui.h"


using namespace SimpleRender;
using namespace std;

RenderScene::RenderScene(int width, int height)
{
	// initialise a frame buffer
	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

	glGenTextures(1, &screenTexture);
	glBindTexture(GL_TEXTURE_2D, screenTexture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, screenTexture, 0);

	GLuint renderBuffer;
	glGenRenderbuffers(1, &renderBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);

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


	this->width = width;
	this->height = height;

}

void RenderScene::DrawScene()
{
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for(auto& object : *SceneObjects)
	{
		object->Draw();
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	
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

	SceneObjects->push_back(new RenderObject(this, (*SceneShaderPrograms)[0], ""));
	ActiveObject = (*SceneObjects)[0];

	SceneCameras->push_back(new RenderCamera());
	ActiveCamera = (*SceneCameras)[0];


}