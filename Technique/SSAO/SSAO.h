#pragma once
#include "../../shader.h"
#include <glm/glm.hpp>

class SSAO : public Shader
{
private:
	GLuint positionTex;
	GLuint normalTex;
	GLuint albedoTex;
	GLuint depthTex;

	GLuint depthFBO;

	glm::vec4 samplingPoints[256];

	GLuint renderPassIndex1_vs;
	GLuint renderPassIndexDebug_vs;

	GLuint renderPassIndex1_fs;
	GLuint renderPassIndex2_fs;
	GLuint renderPassIndexDebug_fs;
	
	int depthWidth;
	int depthHeight;

	bool InitFBO();

public:
	SSAO(const int& w, const int& h);
	~SSAO();

	void Resize(const int& w, const int& h);

	void BeginRenderDepth();
	void EndRenderDepth();

	void BeginRender();
	void EndRender();

	void DebugRender();
};

