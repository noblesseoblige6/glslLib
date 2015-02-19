#include "shaderHandle.h"


shaderHandle::shaderHandle(void)
{
	init("");
}

shaderHandle::~shaderHandle(void)
{}

shaderHandle::shaderHandle(string& shader)
{
	init(shader);
}
void shaderHandle::init(string&)
{
	switch(shader){
	case "Phong":
		shader = new PhongShader();
		break;
	default:
		break;
	}
}
void shaderHandle::use()
{
	shader.useShader();
}

template<typename T> bool shaderHandle::setUniforms(T val, string& name)
{
	shader.setUniform(val, name);
}