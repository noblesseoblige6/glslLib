#include <iostream>
#include <glm/glm.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>

#include "shaderHandle.h"
#include "glHandle.h"
#include "ModelHandle.h"

glHandle Ghandle;
shaderHandle Phandle;
ModelHandle model;

int Height, Width;
float Near, Far;
glm::mat4 Projection;
glm::mat4 View;
glm::mat4 Model;

void initProgram()
{
	Phandle.init(TOON);
	Phandle.printVariables(ATTRIBUTE);
	Phandle.printVariables(UNIFORM);
	//model = ModelHandle(MESH, "./mesh/bs_ears.obj", true);
	model = ModelHandle(TEAPOT, 100, glm::mat4(1.0f));;
}

void setMatrices()
{
	Model = glm::mat4(1.0);
	Model *= glm::rotate(-45.0f, glm::vec3(1.0f,0.0f,0.0f));
	glm::vec4 lightPos = glm::vec4(5.0f,5.0f,2.0f,1.0f);

	glm::mat4 modelView = View * Model;
	Phandle.setParameter("Ka", glm::vec3(0.6, 0.6, 0.6));
	Phandle.setParameter("Kd", glm::vec3(0.9f, 0.6f, 0.8f));
	Phandle.setParameter("Light.intensity", glm::vec3(0.2, 0.2, 0.2));
	Phandle.setParameter("Light.position", View*lightPos);
	Phandle.setParameter("MVP", Projection*modelView);
	Phandle.setParameter("ModelViewMatrix", modelView);
	Phandle.setParameter("NormalMatrix", glm::mat3(  glm::vec3(modelView[0]),  glm::vec3(modelView[1]),  glm::vec3(modelView[2]) ));
}

void display()
{
	glEnable(GL_DEPTH_TEST);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	setMatrices();
	model.render();

	glutSwapBuffers();
}

void resize(int w, int h)
{
	Width = w;
	Height = h;
	Near = 0.1f;
	Far = 100.0f;

	glViewport(0, 0, w, h);	
	Projection = glm::perspective(45.0f, (float)Height/Width, Near, Far);
	View = glm::lookAt(glm::vec3(0.0f, 0.0f, 10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

void key(unsigned char key, int x, int y)
{
	switch(key){
	case 27:
		exit(EXIT_SUCCESS);
		break;
	}
}

int main(int argc, char* argv[])
{
	//tmp code
	//has to create window before glewInit
	glutInit(&argc,argv);
	glutInitWindowPosition(100, 100);

	glutInitWindowSize(500, 500);
	glutInitDisplayMode(GLUT_RGBA| GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("GLEW");
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutKeyboardFunc(key);
	Ghandle.init();
	initProgram();
	glutMainLoop();
	return 0;
}

