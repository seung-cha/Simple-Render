#include "RenderShader.h"
#include <iostream>


using namespace SimpleRender;
using namespace std;


RenderShader::RenderShader(enum ShaderType type)
{
	this->type = type;
	
	CreateShader();
}

RenderShader::RenderShader(enum ShaderType type, string source)
{
	this->type = type;
	CreateShader();
}



void RenderShader::CreateShader()
{
	GLenum t;
	if(type == ShaderType::Fragment)
	{
		t = GL_FRAGMENT_SHADER;
	}
	else if(type == ShaderType::Vertex)
	{
		t = GL_VERTEX_SHADER;
	}
	else if(type == ShaderType::Geometry)
	{
		t = GL_GEOMETRY_SHADER;
	}

	shaderID = glCreateShader(t);
}

bool RenderShader::CompileShader()
{
	if(state == ShaderState::Compiled)
		return true;

	glCompileShader(shaderID);

	GLint compileStatus;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compileStatus);

	if(compileStatus == GL_TRUE)
	{
		state = ShaderState::Compiled;
		return true;
	}



	state = ShaderState::Error;
	cerr << "Shader compilation failed. Error log:" << endl;

	char log[512];
	glGetShaderInfoLog(shaderID, 512, NULL, log);

	cerr << log << endl;
	return false;

}



