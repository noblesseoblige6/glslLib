#pragma once
#include "Shader.h"

#include <string>

using std::string;

class shaderHandle
{
public:
	
	shaderHandle(void);
	~shaderHandle(void);
	shaderHandle(string&);
	void init(string&);
	void use();
	template<typename T> bool setUniforms(T val, string&);

private:
	bool setProgram();
	Shader shader; 
};

