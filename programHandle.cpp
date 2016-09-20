#include "programHandle.h"

#include<cstdio>
#include <sys/stat.h>
#include <iostream>
#include <fstream>

using std::ifstream;
using std::ios;

#include <sstream>
using std::ostringstream;


programHandle::programHandle(void) : program(-1), logText(""){}


programHandle::~programHandle(void){}

void programHandle::printLog()
{
	printf("%s\n", logText.c_str());
}

bool programHandle::fileExists(const string& file)
{
	struct stat fileInfo;
	int res = -1;
	res = stat(file.c_str(), &fileInfo);

	return res == 0;
}

bool programHandle::loadShader(const string& file, GLSL_SHADER::SHADER_TYPE shaderType)
{

	if(!fileExists(file)){
		switch(shaderType){
		case GLSL_SHADER::VERTEX:
			logText = "Theris no such vertex file";
		break;
		case GLSL_SHADER::FRAGMENT:
			logText = "Theris no such fragment file";
		break;
		case GLSL_SHADER::GEOMETRY:
			logText = "Theris no such geomety file";
		break;
		case GLSL_SHADER::TESS_CONTROL:
			logText = "Theris no such tess control file";
		break;
		case GLSL_SHADER::TESS_EVALUATION:
			logText = "Theris no such tess evaluation file";
		break;
		default:
			return false;
		}
		printLog();
		return false;
	}

	//The contents of the file is loaded
	ifstream ifs(file, ios::in);
	if(!ifs){
		logText = "Fail to open the file";
		printLog();
		return false;
	}

	ostringstream code("");
	while(ifs.good()){
		int c = ifs.get();
		if(!ifs.eof()){
			code<<(char)c;
		}
	}
	ifs.close();

	return compileShader(code.str(), shaderType);
}

bool programHandle::compileShader(const string& src, GLSL_SHADER::SHADER_TYPE shaderType)
{
	if(program <= 0){
		program = glCreateProgram();
		if(program == 0){
			logText = "Unable to create program";
			printLog();
			return false;
		}
	}

	int shader = 0;
	switch(shaderType){
		case GLSL_SHADER::VERTEX:
			shader = glCreateShader(GL_VERTEX_SHADER);
		break;
		case GLSL_SHADER::FRAGMENT:
			shader = glCreateShader(GL_FRAGMENT_SHADER);
		break;
		case GLSL_SHADER::GEOMETRY:
			shader = glCreateShader(GL_GEOMETRY_SHADER);
		break;
		case GLSL_SHADER::TESS_CONTROL:
			shader = glCreateShader(GL_TESS_CONTROL_SHADER);
		break;
		case GLSL_SHADER::TESS_EVALUATION:
			shader = glCreateShader(GL_TESS_EVALUATION_SHADER);
		break;
		default:
			return false;
		}
	const char* cCode = src.c_str();
	glShaderSource(shader, 1, &cCode, NULL);
	glCompileShader(shader);

	int res;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &res);
	if(res == GL_FALSE){
		int length = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
		char* cLog = new char[length];
		int written;
		glGetShaderInfoLog(shader, length, &written, cLog);
		logText = cLog;
		printLog();
		delete[] cLog; 
	}
	else{
		glAttachShader(program, shader);
	}
	return true;
}

bool programHandle::linkProgram()
{
	if(program <= 0){
		logText = "There is no program object";
		return false;
	}

	glLinkProgram(program);

	int status = 0;
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	if(status == GL_FALSE){
		int length = 0;
		logText = "";

		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
		if(length > 0){
			char* c_log = new char[length];
			int written = 0;
			glGetProgramInfoLog(program, length, &written, c_log);
			logText = c_log;
			printLog();
			delete[] c_log;
		}
	return false;
	}
	else{
		return true;
	}
}

void programHandle::bindAttribLocation(GLuint location, const char* name)
{
	glBindAttribLocation(program, location, name);
}

void programHandle::bindFragDataLocation(GLuint location, const char* name)
{
	glBindFragDataLocation(program, location, name);
}

void programHandle::useProgram()
{
	if(program <= 0){
		logText = "There is no program object";
		return;
	}
	glUseProgram(program);
}

GLint programHandle::getUniformLocation(const string& name)
{
	return glGetUniformLocation(program, name.c_str());
}

void programHandle::setUniform(const string& name, int val)
{
	GLuint loc = getUniformLocation(name);
	if(loc >= 0){
		glUniform1i(loc, val);
	}
	else{
		logText = "Not found uniform named" +name;
		printLog();
	}
}

void programHandle::setUniform(const string& name, float val)
{
	GLuint loc = getUniformLocation(name);
	if(loc >= 0){
		glUniform1f(loc, val);
	}
	else{
		logText = "Not found uniform named" +name;
		printLog();
	}
}

void programHandle::setUniform(const string& name, double val)
{
	GLuint loc = getUniformLocation(name);
	if(loc >= 0){
		glUniform1d(loc, val);
	}
	else{
		logText = "Not found uniform named" +name;
		printLog();
	}
}

void programHandle::setUniform(const string& name, glm::vec2 vec)
{
	GLuint loc = getUniformLocation(name);
	if(loc >= 0){
		glUniform2fv(loc, 1, glm::value_ptr(vec));
	}
	else{
		logText = "Not found uniform named" +name;
		printLog();
	}
}

void programHandle::setUniform(const string& name, glm::vec3 vec)
{
	GLuint loc = getUniformLocation(name);
	if(loc >= 0){
		glUniform3fv(loc, 1, glm::value_ptr(vec));
	}
	else{
		logText = "Not found uniform named" +name;
		printLog();
	}
}

void programHandle::setUniform(const string& name, glm::vec4 vec)
{
	GLuint loc = getUniformLocation(name);
	if(loc >= 0){
		glUniform4fv(loc, 1, glm::value_ptr(vec));
	}
	else{
		logText = "Not found uniform named" +name;
		printLog();
	}
}

void programHandle::setUniform(const string& name, glm::mat3 mat)
{
	GLuint loc = getUniformLocation(name);
	if(loc >= 0){
		glUniformMatrix3fv(loc, 1, GL_FALSE, glm::value_ptr(mat));
	}
	else{
		logText = "Not found uniform named" +name;
		printLog();
	}
}

void programHandle::setUniform(const string& name, glm::mat4 mat)
{
	GLuint loc = getUniformLocation(name);
	if(loc >= 0){
		glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(mat));
	}
	else{
		logText = "Not found uniform named" +name;
		printLog();
	}
}

bool programHandle::validateProgram()
{
	GLint status;
	glValidateProgram(program);
	glGetProgramiv(program, GL_VALIDATE_STATUS, &status);
	if(status == GL_FALSE){
		int length;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
		if(length > 0){
			int written = 0;
			char* c_log = new char[length];
			glGetProgramInfoLog(program, length, &written, c_log);
			logText = c_log;
			printLog();
			delete[] c_log;
		}
		
		return false;
	}
	return true;
}

void programHandle::printAttributes()
{
	GLint num, length, size, location;
	GLsizei written;
	GLenum type;
	glGetProgramiv(program, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &length);
	glGetProgramiv(program, GL_ACTIVE_ATTRIBUTES, &num);

	char* c_log = new char[length];
	printf("-----Attributes name and location-----\n");
	for(int i = 0; i < num; i++){
		glGetActiveAttrib(program, i, length, &written, &size, &type, c_log);
		location = glGetAttribLocation(program, c_log);
		printf("Location: %d  Name: %s\n", location, c_log);
	}
	printf("--------------------------------------\n");
	delete[] c_log;
}

void programHandle::printUniforms()
{
	GLint num, length, size, location;
	GLsizei written;
	GLenum type;
	glGetProgramiv(program, GL_ACTIVE_UNIFORM_MAX_LENGTH, &length);
	glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &num);

	char* c_log = new char[length];
	printf("-----Uniforms name and location-----\n");
	for(int i = 0; i < num; i++){
		glGetActiveUniform(program, i, length, &written, &size, &type, c_log);
		location = glGetUniformLocation(program, c_log);
		printf("Location: %d  Name: %s\n", location, c_log);
	}
	printf("--------------------------------------\n");
	delete[] c_log;
}

int programHandle::getProgram()
{
	return program;
}

int programHandle::getProgram() const
{
	return program;
}