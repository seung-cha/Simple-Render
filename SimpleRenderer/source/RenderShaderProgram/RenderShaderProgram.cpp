#include "RenderShaderProgram.h"
#include <iostream>
#include "RenderObject/RenderObject.h"


using namespace SimpleRender;
using namespace std;


RenderShaderProgram::RenderShaderProgram()
{
	programID = glCreateProgram();
}

SimpleRender::RenderShaderProgram::~RenderShaderProgram()
{

	auto copy = associatedObjects;
	//ReplaceShaderProgram() modifies the vector by erasing the reference of itself.

	for(auto& object : copy)
	{
		object->ReplaceShaderProgram(nullptr);
	}


	glDeleteProgram(programID);
	for(int i = 0; i < 3; i++)
	{
		if(shaders[i])
		{
			shaders[i]->ParentShaderPrograms->erase(this);
		}
	}

	for(auto& data : programData)
	{
		delete(data);
	}

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


void SimpleRender::RenderShaderProgram::AttachShader(RenderShader* shader)
{
	GLenum type = shader->Type();

	// Detach the shader from the program if exists
	if(shaders[type])
	{
		glDetachShader(programID, shaders[type]->ID());
		shaders[type]->ParentShaderPrograms->erase(this);
	}


	shaders[type] = shader;
	shaders[type]->ParentShaderPrograms->insert(this);
	glAttachShader(programID, shaders[type]->ID());

	std::cout << "Attached a " << RenderShader::ShaderTypeToString(shader->Type()) << " shader" << std::endl << std::endl;
}


void RenderShaderProgram::AddUniformData(ShaderProgramData* data)
{
	programData.push_back(data);


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
