#pragma once
#include <GL/glew.h>
#include <GL/gl.h>

#include <string>
using std::string;

#include <glm\glm.hpp>


namespace GLSL_SHADER {
	enum SHADER_TYPE{
		VERTEX = 0,
		FRAGMENT = 1,
		GEOMETRY = 2,
		TESS_CONTROL = 3,
		TESS_EVALUATION = 4
	};
};

class programHandle
{
private:
	int handle;
	string logText;
	bool compileShader(const string&, GLSL_SHADER::SHADER_TYPE);
	bool linkProgram();
	void printLog();
	bool fileExists(const string&);

public:
	programHandle(void);
	~programHandle(void);
	bool loadShader(const string&, GLSL_SHADER::SHADER_TYPE);
	void useProgram();

	void setUniform(const string&, int);
	void setUniform(const string&, float);
	void setUniform(const string&, double);
	void setUniform(const string&, glm::vec3);
	void setUniform(const string&, glm::vec4);
	void setUniform(const string&, glm::mat3x3);
	void setUniform(const string&, glm::mat4x4);
};

