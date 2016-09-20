#pragma once
#include "Handle/programHandle.h"

class Shader:public programHandle
{
public:
	Shader(void);
	Shader(const string&, const string&);
	~Shader(void);
	void init(const string&, const string&);
	void useShader();
	void printVariables();
};
