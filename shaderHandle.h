#pragma once
#include "programHandle.h"
#include <vector>
#include <string>

using std::vector;
using std::string;

namespace GLSL_SHADER {
	enum SHADER_TYPE{
		VERTEX = 0,
		FRAGMENT = 1,
		GEOMETRY = 2,
		TESS_CONTROL = 3,
		TESS_EVALUATION = 4
	};
	enum SHADER{
		Phong = 0
	};
};

class shaderHandle
{
public:
	
	shaderHandle(void);
	~shaderHandle(void);
	void createShader(const string& vertex, const string& fragment);
	void createPreparedShader(GLSL_SHADER::SHADER);
private:
	vector<programHandle> programs;
	
};

