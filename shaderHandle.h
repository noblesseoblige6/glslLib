#pragma once
#include "Shader.h"

#include <glm/glm.hpp>
#include <string>

using std::string;
using glm::vec3;

enum SHADER_NAME{
	PHONG = 0
};
enum SHADER_VARIABLE{
UNIFORM = 0,
ATTRIBUTE = 1
};

class shaderHandle
{
public:
	shaderHandle(void);
	~shaderHandle(void);
	shaderHandle(SHADER_NAME);
	void init(SHADER_NAME);
	void use();
	void setParameter(const string&, int );
	void setParameter(const string&, float );
	void setParameter(const string&, double );
	void setParameter(const string&, bool);
	void setParameter(const string&, glm::vec2 );
	void setParameter(const string&, glm::vec3 );
	void setParameter(const string&, glm::vec4 );
	void setParameter(const string&, glm::mat3 );
	void setParameter(const string&, glm::mat4 );
	void printVariables(SHADER_VARIABLE);
	
private:
	bool setProgram();
	Shader* shader; 
};

