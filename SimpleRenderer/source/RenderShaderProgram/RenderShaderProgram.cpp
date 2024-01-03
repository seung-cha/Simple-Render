#include "RenderShaderProgram.h"
#include <iostream>
#include "RenderObject/RenderObject.h"


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

void RenderShaderProgram::Dispose()
{
	auto copy = associatedObjects;

	for(auto& object : copy)
	{
		object->ReplaceShaderProgram(nullptr);
	}

	for(int i = 0; i < 3; i++)
	{
		if(shaders[i])
		{
			shaders[i]->ParentShaderPrograms->erase(this);
		}
	}

	

	glDeleteProgram(programID);
}

void RenderShaderProgram::ApplyUniformVariables()
{
	glUseProgram(programID);

	for(auto& data : programData)
	{
		data->Apply(programID);

	}

	glUseProgram(0);
}
