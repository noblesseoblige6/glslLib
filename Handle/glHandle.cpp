#include "glHandle.h"
#include <iostream>

glHandle::glHandle(void)
{
}


glHandle::~glHandle(void)
{
}


void glHandle::init()
{
	int err = glewInit();
	if (err != GLEW_OK) {
		std::cerr << glewGetErrorString(err) << std::endl;
		exit(EXIT_FAILURE);
	}

	// 浮動小数点テクスチャが使えるかチェック
	if (!GLEW_ARB_texture_float)
	{
		std::cerr << "Error : ARB_texture_float is not supported." << std::endl;
		exit(EXIT_FAILURE);
	}
}

int glHandle::GetNumOfTextureUnit()
{
	// テクスチャ最大数
	GLint num_tex_units;
	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &num_tex_units);
	return num_tex_units;
}

int glHandle::GetNumOfUniformInVert()
{
	GLint num;
	glGetIntegerv(GL_MAX_VERTEX_UNIFORM_VECTORS, &num);
	return num;
}

int glHandle::GetNumOfUniformInFrag()
{
	GLint num;
	glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_VECTORS, &num);
	return num;
}

int glHandle::GetNumOfAttribute()
{
	GLint num;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &num);
	return num;
}

int glHandle::GetNumOfVarying()
{
	GLint num;
	glGetIntegerv(GL_MAX_VARYING_VECTORS, &num);
	return num;
}