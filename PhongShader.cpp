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

void PhongShader::BeginRender(void)
{
	glEnable(GL_DEPTH_TEST);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void PhongShader::EndRender()
{
}
