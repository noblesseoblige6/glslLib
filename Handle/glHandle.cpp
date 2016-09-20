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
	if (err != GLEW_OK){
		std::cout<<glewGetErrorString(err)<<std::endl;
		exit(EXIT_FAILURE);
	}
}