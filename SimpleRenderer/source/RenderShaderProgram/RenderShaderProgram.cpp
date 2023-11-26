#include "RenderShaderProgram.h"



using namespace SimpleRender;



RenderShaderProgram::RenderShaderProgram()
{
	programID = glCreateProgram();
}