#include "programHandle.h"

#include <sys/stat.h>
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