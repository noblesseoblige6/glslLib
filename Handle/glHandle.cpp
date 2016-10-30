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

	// ���������_�e�N�X�`�����g���邩�`�F�b�N
	if (!GLEW_ARB_texture_float)
	{
		std::cerr << "Error : ARB_texture_float is not supported." << std::endl;
		exit(EXIT_FAILURE);
	}
}