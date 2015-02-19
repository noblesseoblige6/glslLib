#include "PhongShader.h"


PhongShader::PhongShader(void)
{
	loadShader("./shader/Lighting/PhongShading.vs", GLSL_SHADER::VERTEX);
	loadShader("./shader/Lighting/PhongShading.fs", GLSL_SHADER::FRAGMENT);
	linkProgram();
	useProgram();
}

PhongShader::~PhongShader(void)
{
}