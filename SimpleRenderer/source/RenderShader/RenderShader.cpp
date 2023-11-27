#include "RenderShader.h"
#include <iostream>
#include "FileReader/FileReader.h"

using namespace SimpleRender;
using namespace std;


RenderShader::RenderShader(enum ShaderType type)
{
	this->type = type;
	CreateShader();
}

RenderShader::RenderShader(enum ShaderType type, string path)
{
	this->type = type;
	
	CreateShader();
	ShaderSource(path);
	CompileShader();
	
}

void RenderShader::ShaderSource(std::string path)
{
	this->path = path;

	const char* src = FileReader::ReadFile(path.c_str());
	// Free the source if it already exists
	if(source)
	{
		free((void*)source);
		cout << "Replacing shader source" << endl << endl;
	}
	else
	cout << "Adding shader source" << endl << endl;

	source = src;

	glShaderSource(shaderID, 1, &source, NULL);
}




void RenderShader::CreateShader()
{
	GLenum t;
	string stype;

	if(type == ShaderType::Fragment)
	{
		t = GL_FRAGMENT_SHADER;
		stype = "Fragment";
	}
	else if(type == ShaderType::Vertex)
	{
		t = GL_VERTEX_SHADER;
		stype = "Vertex";
	}
	else if(type == ShaderType::Geometry)
	{
		t = GL_GEOMETRY_SHADER;
		stype = "Geometry";
	}

	shaderID = glCreateShader(t);
	cout << stype << " shader created. Waiting to be compiled." << endl;
	cout << path << endl << endl;
}

bool RenderShader::CompileShader()
{
	cout << "Compiling Shader: " << endl;
	cout << path << endl;

	if(state == ShaderState::ShaderCompiled)
	{
		cout << "Shader is already compiled" << endl;
		return true;
	}

	glCompileShader(shaderID);

	GLint compileStatus;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compileStatus);

	if(compileStatus == GL_TRUE)
	{
		cout << "Shader is compiled successfully." << endl << endl;
		state = ShaderState::ShaderCompiled;
		return true;
	}



	state = ShaderState::ShaderError;
	cerr << "Shader compilation failed. Error log:" << endl << endl;

	char log[512];
	glGetShaderInfoLog(shaderID, 512, NULL, log);

	cerr << log << endl;
	return false;

}



