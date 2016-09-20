#include "SSAO.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include <iostream>
#include <random>

SSAO::SSAO(const int& w, const int& h)
{

	loadShader("./shader/SSAO/SSAO.vert", GLSL_SHADER::VERTEX);
	loadShader("./shader/SSAO/SSAO.frag", GLSL_SHADER::FRAGMENT);
	linkProgram();
	useProgram();

	renderPassIndex1_vs = glGetSubroutineIndex(getProgram(), GL_VERTEX_SHADER, "render");
	renderPassIndexDebug_vs = glGetSubroutineIndex(getProgram(), GL_VERTEX_SHADER, "renderDebug");

	renderPassIndex1_fs = glGetSubroutineIndex(getProgram(), GL_FRAGMENT_SHADER, "renderDepth");
	renderPassIndex2_fs = glGetSubroutineIndex(getProgram(), GL_FRAGMENT_SHADER, "render");
	renderPassIndexDebug_fs = glGetSubroutineIndex(getProgram(), GL_FRAGMENT_SHADER, "renderDebug");

	depthWidth = w;
	depthHeight = h;

	if (!InitFBO())
		std::cerr << "Failed to init FBO" << std::endl;

	setUniform("DepthMap", 0);
	setUniform("PositionMap", 1);
	setUniform("NormalMap", 2);
	setUniform("AlbedoMap", 3);

	// Create sample points
	std::random_device rd;
	std::mt19937 mt(rd());

	std::uniform_real_distribution<double> wgt(0.0, 1.0);
	std::uniform_real_distribution<double> rnd(-1.0, 1.0);
	std::uniform_real_distribution<double> ang(0.0, 2.0*M_PI);

	for (int i = 0; i < 256; ++i)
	{
		float u = wgt(mt);
		float r = 2.0f * u;
		float v = rnd(mt); //-1.0~1.0
		float sq = sqrtf(1.0f - v * v);
		float theta = ang(mt);
		float cost = cos(theta);
		float sint = sin(theta);

		samplingPoints[i].x = r * cost;
		samplingPoints[i].y = r * sint;
		samplingPoints[i].z = r * v;
		samplingPoints[i].w = 1.0f;

		char str[256];
		sprintf(str, "SamplePoints[%d]", i);
		setUniform(str, samplingPoints[i]);
	}
}

SSAO::~SSAO()
{
}

void SSAO::Resize(const int& w, const int& h)
{
	depthWidth = w;
	depthHeight = h;

	InitFBO();
}

bool SSAO::InitFBO()
{
	glGenFramebuffers(1, &depthFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, depthFBO);
	{
		// Create texture to attach frame buffer
		glActiveTexture(GL_TEXTURE0);
		glGenTextures(1, &depthTex);
		glBindTexture(GL_TEXTURE_2D, depthTex);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, depthWidth, depthHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTex, 0);

		// Create position texture
		glActiveTexture(GL_TEXTURE1);
		glGenTextures(1, &positionTex);
		glBindTexture(GL_TEXTURE_2D, positionTex);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, depthWidth, depthHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, positionTex, 0);

		// Create normal texture
		glActiveTexture(GL_TEXTURE2);
		glGenTextures(1, &normalTex);
		glBindTexture(GL_TEXTURE_2D, normalTex);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, depthWidth, depthHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, normalTex, 0);

		// Create position texture
		glActiveTexture(GL_TEXTURE3);
		glGenTextures(1, &albedoTex);
		glBindTexture(GL_TEXTURE_2D, albedoTex);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, depthWidth, depthHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, albedoTex, 0);


		GLenum drawBuffers[] = { GL_NONE , 
			                     GL_COLOR_ATTACHMENT0, 
			                     GL_COLOR_ATTACHMENT1,  
			                     GL_COLOR_ATTACHMENT2 };
		glDrawBuffers(4, drawBuffers);


		GLenum result = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		if (result == GL_FRAMEBUFFER_COMPLETE) {
			std::cout << "Framebuffer is complete." << std::endl;
		}
		else {
			std::cerr << "Framebuffer is not complete." << std::endl;
			return false;
		}

		glBindTexture(GL_TEXTURE_2D, NULL);
	}
	glBindFramebuffer(GL_FRAMEBUFFER, NULL);

	return true;
}

void SSAO::BeginRenderDepth()
{	
	glBindFramebuffer(GL_FRAMEBUFFER, depthFBO);

	glEnable(GL_DEPTH_TEST);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glUniformSubroutinesuiv(GL_VERTEX_SHADER, 1, &renderPassIndex1_vs);
	glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &renderPassIndex1_fs);
}

void SSAO::EndRenderDepth()
{
	glFinish();

	glBindFramebuffer(GL_FRAMEBUFFER, NULL);
}

void SSAO::BeginRender()
{
	glBindFramebuffer(GL_FRAMEBUFFER, NULL);

	glBindTexture(GL_TEXTURE_2D, depthTex);

	glEnable(GL_DEPTH_TEST);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glUniformSubroutinesuiv(GL_VERTEX_SHADER, 1, &renderPassIndex1_vs);
	glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &renderPassIndex2_fs);
}

void SSAO::EndRender()
{
	glFinish();
}

void SSAO::DebugRender()
{
	glViewport(0, 0, depthWidth, depthHeight);

	glDisable(GL_DEPTH_TEST);

	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glUniformSubroutinesuiv(GL_VERTEX_SHADER, 1, &renderPassIndexDebug_vs);
	glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &renderPassIndexDebug_fs);

	glBindTexture(GL_TEXTURE_2D, positionTex);
	glBindTexture(GL_TEXTURE_2D, normalTex);
	glBindTexture(GL_TEXTURE_2D, albedoTex);
	{
		glBegin(GL_QUADS);
		glVertex2d(0.0, 0.0);
		glVertex2d(1.0, 0.0);
		glVertex2d(1.0, 1.0);
		glVertex2d(0.0, 1.0);
		glEnd();
	}
	glBindTexture(GL_TEXTURE_2D, NULL);

	glFinish();
}