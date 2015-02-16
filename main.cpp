#include <iostream>
#include <glm/glm.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>

#include "programHandle.h"
#include "glHandle.h"
#include "vbotorus.h"

glHandle Ghandle;
programHandle Phandle;
VBOTorus* torus;

int Height, Width;
float Near, Far;
glm::mat4 Projection;
glm::mat4 View;
glm::mat4 Model;

void initProgram()
{
	Phandle.loadShader("diffuse.vert", GLSL_SHADER::VERTEX);
	Phandle.loadShader("diffuse.frag", GLSL_SHADER::FRAGMENT);
	Phandle.linkProgram();
	Phandle.useProgram();
}

void setMatrices()
{

	Model = glm::mat4(1.0f);
	Model *= glm::rotate(-35.0f, glm::vec3(1.0f,0.0f,0.0f));
    Model *= glm::rotate(35.0f, glm::vec3(0.0f,1.0f,0.0f));
	glm::vec4 lightPos = glm::vec4(5.0f,5.0f,2.0f,1.0f);
	glm::vec3 materialIntensity = glm::vec3(0.9f, 0.5f, 0.3f);
	glm::vec3 lightIntensity = glm::vec3(1.0f, 1.0f, 1.0f);

	glm::mat4 modelView = View * Model;
	Phandle.setUniform("ModelViewMatrix", modelView);
	Phandle.setUniform("MVP", Projection*modelView);
	Phandle.setUniform("Kd", materialIntensity);
	Phandle.setUniform("Ld", lightIntensity);
	Phandle.setUniform("LightPosition", View*lightPos);
	Phandle.setUniform("NormalMatrix", glm::mat3(  glm::vec3(modelView[0]),  glm::vec3(modelView[1]),  glm::vec3(modelView[2]) ));
}

void display()
{
	glEnable(GL_DEPTH_TEST);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	torus = new VBOTorus(0.7, 0.3, 40, 40);
	
	setMatrices();
	torus->render();
	glutSwapBuffers();
}

void resize(int w, int h)
{
	Width = w;
	Height = h;
	Near = 0.1f;
	Far = 100.0f;
	
	glViewport(0,0,w,h);	
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

