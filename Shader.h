#pragma once
#include "programHandle.h"

class Shader
{
private:
	programHandle program;

public:
	Shader(void);
	~Shader(void);
	virtual bool init();
	void useShader();
};

