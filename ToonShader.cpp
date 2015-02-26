#include "ToonShader.h"


ToonShader::ToonShader(void)
{
	loadShader("./shader/Lighting/ToonShading.vert", GLSL_SHADER::VERTEX);
	loadShader("./shader/Lighting/ToonShading.frag", GLSL_SHADER::FRAGMENT);
	linkProgram();
	useProgram();
}


ToonShader::~ToonShader(void)
{
}
