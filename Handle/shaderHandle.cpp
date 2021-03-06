#include "shaderHandle.h"

shaderHandle::shaderHandle(void){}

shaderHandle::~shaderHandle(void)
{
delete shader;
}

shaderHandle::shaderHandle(SHADER_NAME shaderName)
{
	init(shaderName);
}

void shaderHandle::init(SHADER_NAME shaderName)
{
	switch(shaderName){
	case PHONG:
		shader = new PhongShader();
		break;
	case TOON:
		shader = new ToonShader();
		break;
	case DEPTHSHADOW:
		shader = new DepthShadow();
	case AO:
		shader = new SSAO(256, 256);
	default:
		break;
	}
}

void shaderHandle::use()
{
	shader->useShader();
}

void shaderHandle::printVariables(SHADER_VARIABLE val)
{
	switch(val){
	case ATTRIBUTE:
		shader->printAttributes();
		break;
	case UNIFORM:
		shader->printUniforms();
		break;
	default:
		break;
	}
}

void shaderHandle::setParameter(const string& name, int val)
{
	shader->setUniform(name, val);
}
void shaderHandle::setParameter(const string& name, float val)
{
	shader->setUniform(name, val);
}
void shaderHandle::setParameter(const string& name, double val)
{
	shader->setUniform(name, val);
}
void shaderHandle::setParameter(const string& name, glm::vec2 vec)
{
	shader->setUniform(name, vec);
}
void shaderHandle::setParameter(const string& name, glm::vec3 vec)
{
	shader->setUniform(name, vec);
}
void shaderHandle::setParameter(const string& name, glm::vec4 vec)
{
	shader->setUniform(name, vec);
}
void shaderHandle::setParameter(const string& name, glm::mat3 mat)
{
	shader->setUniform(name, mat);
}
void shaderHandle::setParameter(const string& name, glm::mat4 mat)
{
	shader->setUniform(name, mat);
}

Shader* shaderHandle::getShader()
{
	return shader;
}