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
	//GLuint sampleTex;

	GLuint depthFBO;

	GLuint renderPass_GBuufer_vs;
	GLuint renderPass_Render_vs;

	GLuint renderPass_GBuufer_fs;
	GLuint renderPass_Render_fs;

	int depthWidth;
	int depthHeight;

	bool InitFBO();

public:
	SSAO(const int& w, const int& h);
	~SSAO();

	GLuint sampleTex;

	void Resize(const int& w, const int& h);

	void BeginRenderGBuffer();
	void EndRenderGBuffer();

	void Render();
};

