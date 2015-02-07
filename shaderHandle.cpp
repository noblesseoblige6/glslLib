#include "shaderHandle.h"


shaderHandle::shaderHandle(void)
{}

shaderHandle::~shaderHandle(void)
{}

void shaderHandle::createShader(const string& vertex, const string& fragment)
{
programHandle prg;
prg.loadShader(vertex, GLSL_SHADER::SHADER_TYPE::VERTEX);
prg.loadShader(fragment, GLSL_SHADER::SHADER_TYPE::FRAGMENT);
prg.linkProgram();

programs.push_back(prg);
}

void createPreparedShader(GLSL_SHADER::SHADER shader)
{
	
}