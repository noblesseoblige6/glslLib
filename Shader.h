#pragma once
#include "programHandle.h"
#include <glm/glm.hpp>


class Shader : public programHandle
{
public:
	Shader(void);
	Shader(const string&, const string&);

	~Shader(void);
	void init(const string&, const string&);
	void useShader();
	void printVariables();
};

