#include "PhongShader.h"


PhongShader::PhongShader(void)
{
	loadShader("./shader/Lighting/PhongShading.vert", GLSL_SHADER::VERTEX);
	loadShader("./shader/Lighting/PhongShading.frag", GLSL_SHADER::FRAGMENT);
	linkProgram();
	useProgram();
}

PhongShader::~PhongShader(void)
{
}