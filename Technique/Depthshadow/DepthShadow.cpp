#include "DepthShadow.h"

DepthShadow::DepthShadow()
{

	loadShader("../../shader/ShadowMap/DepthShadow.vert", GLSL_SHADER::VERTEX);
	loadShader("../../shader/ShadowMap/DepthShadow.frag", GLSL_SHADER::FRAGMENT);
	linkProgram();
	useProgram();

	glEnable(GL_DEPTH_TEST);

	lightFrustum = new Frustum(ProjectionConfig::PERSPECTIVE);

	pass1Index = glGetSubroutineIndex(getProgram(), GL_FRAGMENT_SHADER, "recordDepth");
	pass2Index = glGetSubroutineIndex(getProgram(), GL_FRAGMENT_SHADER, "shadeWithShadow");

	//createDepthMap(256, 256);
}

DepthShadow::~DepthShadow()
{
	delete lightFrustum;
}

bool DepthShadow::createDepthMap(const int& width, const int& height)
{
	depthWidth = width;
	depthHeight = height;

	GLfloat border[] = { 1.0f, 0.0f,0.0f,0.0f };

	glGenTextures(1, &depthTex);
	glBindTexture(GL_TEXTURE_2D, depthTex);
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, depthWidth,
			depthHeight, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, border);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LESS);

		// Assign the depth buffer texture to texture channel 0
		glActiveTexture(GL_TEXTURE0);
	}
	
	// Create and set up the FBO
	glGenFramebuffers(1, &shadowFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, shadowFBO);
	{
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
			GL_TEXTURE_2D, depthTex, 0);

		GLenum drawBuffers[] = { GL_NONE };
		glDrawBuffers(1, drawBuffers);

		GLenum result = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		if (result == GL_FRAMEBUFFER_COMPLETE) {
			printf("Framebuffer is complete.\n");
		}
		else {
			printf("Framebuffer is not complete.\n");
			return false;
		}
	}
	glBindFramebuffer(GL_FRAMEBUFFER, NULL);
	return true;
}

void DepthShadow::createLightPV(const glm::vec4& lightPos)
{
	shadowBias = mat4(
		vec4(0.5f, 0.0f, 0.0f, 0.0f),
		vec4(0.0f, 0.5f, 0.0f, 0.0f),
		vec4(0.0f, 0.0f, 0.5f, 0.0f),
		vec4(0.5f, 0.5f, 0.5f, 1.0f)
	);
	lightFrustum->orient(vec3(lightPos), glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	lightFrustum->setPerspective(45.0f, 1.0f, 1.0f, 25.0f);
	
	lightPV = shadowBias * lightFrustum->getProjectionMatrix() * lightFrustum->getViewMatrix();
}

const glm::mat4& DepthShadow::getLightPV()
{
	return lightPV;
}

void DepthShadow::setMatrix(const glm::mat4& model)
{
	glm::mat4 view = lightFrustum->getViewMatrix();
	glm::mat4 projection = lightFrustum->getProjectionMatrix();

	glm::mat4 mv = view * model;
	setUniform("ModelViewMatrix", mv);
	setUniform("NormalMatrix",
		glm::mat3(glm::vec3(mv[0]), glm::vec3(mv[1]), glm::vec3(mv[2])));
	setUniform("MVP", projection * mv);
	setUniform("ShadowMatrix", lightPV * model);
}

void DepthShadow::BeginDepthMap()
{
	setUniform("ShadowMap", 0);
	glBindFramebuffer(GL_FRAMEBUFFER, shadowFBO);
	
	glClear(GL_DEPTH_BUFFER_BIT);
	
	glViewport(0, 0, depthWidth, depthHeight);
	glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &pass1Index);
	
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
}

void DepthShadow::EndDepthMap()
{
	glFlush();
	//glFinish();
	
	glBindFramebuffer(GL_FRAMEBUFFER, NULL);
	glDisable(GL_CULL_FACE);
}

void DepthShadow::BeginRenderShadow(const int& width, const int& height)
{
	glViewport(0, 0, width, height);
	glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &pass2Index);
}

void DepthShadow::EndRenderShadow()
{}