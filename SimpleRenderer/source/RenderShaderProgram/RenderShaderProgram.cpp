#include "RenderShaderProgram.h"
#include <iostream>


using namespace SimpleRender;
using namespace std;


RenderShaderProgram::RenderShaderProgram()
{
	programID = glCreateProgram();
}


void RenderShaderProgram::LinkProgram()
{
	cout << "Linking a shader program" << endl;
	glLinkProgram(programID);



	GLint status;
	glGetProgramiv(programID, GL_LINK_STATUS, &status);

	if(status == GL_TRUE)
	{
		cout << "Linking successful." << endl << endl;
		state = ShaderProgramLinked;
		return;
	}

	state = ShaderProgramError;
	cout << "Linking unsuccessful: " << endl;

	char log[512];

	glGetProgramInfoLog(programID, 512, NULL, log);

	cout << log << endl << endl;

}


void RenderShaderProgram::AttachShader(RenderShader* shader)
{
	GLenum type = shader->Type();

	// Detach the shader from the program if exists
	if(shaders[type])
	{
		glDetachShader(programID, shaders[type]->ID());
	}


	shaders[type] = shader;
	glAttachShader(programID, shaders[type]->ID());

	cout << "Attached a " << RenderShader::ShaderTypeToString(shader->Type()) << " shader" << endl << endl;

}
