#pragma once
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/freeglut.h>

#include <string>
using std::string;

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

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
	int program;
	string logText;
	bool compileShader(const string&, GLSL_SHADER::SHADER_TYPE);
	
	void printLog();
	bool fileExists(const string&);
	GLint getUniformLocation(const string&);
public:
	programHandle(void);
	~programHandle(void);
	bool loadShader(const string&, GLSL_SHADER::SHADER_TYPE);
	bool linkProgram();
	void useProgram();

	void bindAttribLocation(GLuint location, const char* name);
	void bindFragDataLocation(GLuint location, const char* name);

	bool validateProgram();
	void printAttributes();
	void printUniforms();
	
	void setUniform(const string&, int);
	void setUniform(const string&, float);
	void setUniform(const string&, double);
	void setUniform(const string&, bool);
	void setUniform(const string&, glm::vec2);
	void setUniform(const string&, glm::vec3);
	void setUniform(const string&, glm::vec4);
	void setUniform(const string&, glm::mat3);
	void setUniform(const string&, glm::mat4);
	int getProgram();
	int getProgram() const;
};

