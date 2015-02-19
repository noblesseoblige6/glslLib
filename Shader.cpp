#include "Shader.h"


Shader::Shader(void)
{
}


Shader::~Shader(void)
{
}

bool Shader::init(){}

void Shader::useShader()
{
	program.useProgram();
}