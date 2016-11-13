#pragma once
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/freeglut.h>

class glHandle
{
public:
	glHandle(void);
	~glHandle(void);
	void init();
	int GetNumOfTextureUnit();
	int GetNumOfUniformInVert();
	int GetNumOfUniformInFrag();
	int GetNumOfAttribute();
	int GetNumOfVarying();

};

