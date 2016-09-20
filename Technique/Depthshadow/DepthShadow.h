#pragma once
#include "Shader.h"
#include "Frustum.h"

class DepthShadow : public Shader
{
private:
	GLuint depthTex;
	GLuint shadowFBO;

	GLuint pass1Index;
	GLuint pass2Index;

	int depthWidth;
	int depthHeight;

	glm::mat4 shadowBias;
	glm::mat4 lightPV;

	Frustum *lightFrustum;

public:
	DepthShadow();
	~DepthShadow();
	bool createDepthMap(const int& width, const int& height);
	void createLightPV(const glm::vec4& lightPos);
	const glm::mat4& getLightPV();
	void setMatrix(const glm::mat4& model);
	void BeginDepthMap();
	void EndDepthMap();
	void BeginRenderShadow(const int& width, const int& height);
	void EndRenderShadow();
};

