#include <iostream>
#include <glm/glm.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>

#include "shaderHandle.h"
#include "glHandle.h"
#include "ModelHandle.h"

glHandle Ghandle;
shaderHandle Phandle;
shaderHandle PhandleTest;
ModelHandle model[2];

int Height, Width;
float Near, Far;

glm::mat4 Projection;
glm::mat4 View;
glm::mat4 Model;

glm::vec4 LightPos = glm::vec4(2.0f, 2.0f, -2.0f, 1.0f);

void initProgram()
{
	Phandle.init(AO);
	
	Phandle.printVariables(ATTRIBUTE);
	Phandle.printVariables(UNIFORM);
	model[0] = ModelHandle(MESH, "./mesh/bs_ears.obj", true);
	//model[0] = ModelHandle(TEAPOT, 10, glm::mat4(1.0));
	//model[1] = ModelHandle(PLANE);

}

void setMatrices(int idx)
{
	Model = glm::mat4(1.0f);
	if (idx == 0) {
		float theta = -(float)PI * 1.0f;
		//Model *= glm::scale(vec3(0.1f, 0.1f, 0.1f));
		//Model *= glm::rotate(theta, glm::vec3(0.0f, 1.0f, 0.0f));
		Model *= glm::translate(glm::vec3(0.0f, 0.0f, 0.0f));
	}

	glm::mat4 modelView = View * Model;
	Phandle.setParameter("Material.Ka", glm::vec3(0.2f, 0.2f, 0.2f));
	Phandle.setParameter("Material.Kd", glm::vec3(0.6f, 0.9f, 0.8f));
	Phandle.setParameter("Material.Ks", glm::vec3(0.0f, 0.0f, 0.0f));
	Phandle.setParameter("Material.Shineness", 100.0f);

	Phandle.setParameter("Light.Intensity", glm::vec3(0.9f, 0.9f, 0.9f));
	Phandle.setParameter("Light.Position", View*LightPos);

	Phandle.setParameter("MVP", Projection*modelView);
	Phandle.setParameter("ProjectionMatrix", Projection);

	Phandle.setParameter("ModelViewMatrix", modelView);
	Phandle.setParameter("NormalMatrix", glm::mat3(glm::vec3(modelView[0]), glm::vec3(modelView[1]), glm::vec3(modelView[2])));

	Phandle.setParameter("Viewport", glm::vec2(Width, Height));

}

void display()
{
	SSAO* pRenderTech = (SSAO*)Phandle.getShader();	
	pRenderTech->useShader();

	pRenderTech->BeginRenderDepth();
	{
		for (int i = 0; i < 1; ++i) {
			setMatrices(i);
			model[i].render();
		}
	}
	pRenderTech->EndRenderDepth();
	
#if 1
	pRenderTech->DebugRender();
#else
	pRenderTech->BeginRender();
	{
		for (int i = 0; i < 2; ++i) {
			setMatrices(i);
			model[i].render();
		}
	}
	pRenderTech->EndRender();
#endif
	
	glutSwapBuffers();
}

void resize(int w, int h)
{
	Width = w;
	Height = h;
	Near = 1.0f;
	Far = 10.0f;

	glViewport(0, 0, w, h);
	Projection = glm::perspective(45.0f, (float)Width / (float)Height, Near, Far);
	View = glm::lookAt(glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	SSAO* pRenderTech = (SSAO*)Phandle.getShader();
	pRenderTech->Resize(Width, Height);
}

void key(unsigned char key, int x, int y)
{
	switch (key) {
	case 27:
		exit(EXIT_SUCCESS);
		break;
	}
}

int main(int argc, char* argv[])
{
	// NOTE:Should create window before glewInit
	glutInit(&argc, argv);
	glutInitWindowPosition(100, 100);

	glutInitWindowSize(512, 512);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("GLEW");
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutKeyboardFunc(key);
	Ghandle.init();
	initProgram();
	glutMainLoop();
	return 0;
}

