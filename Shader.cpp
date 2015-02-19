#include "Shader.h"


Shader::Shader(void)
{
}

Shader::Shader(const string& vert, const string& frag)
{
	loadShader(vert, GLSL_SHADER::VERTEX);
	loadShader(frag, GLSL_SHADER::FRAGMENT);
	linkProgram();
	useProgram();
}

Shader::~Shader(void)
{
}

void Shader::init(const string& vert, const string& frag){
	loadShader(vert, GLSL_SHADER::VERTEX);
	loadShader(frag, GLSL_SHADER::FRAGMENT);
	linkProgram();
	useProgram();
}

void Shader::useShader()
{
	useProgram();
}