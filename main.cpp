#include <iostream>
#include <ctime>
#include <glm/glm.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>

#include "Handle/shaderHandle.h"
#include "Handle/glHandle.h"
#include "Handle/modelHandle.h"
#include "Handle/CameraHandle.h"

#include "Quaternion.h"

glHandle Ghandle;
shaderHandle Phandle;
shaderHandle PhandleTest;
ModelHandle* model[2];
CameraHandle CamHandle;

int Height, Width;
float Near, Far;

glm::mat4 Projection;

bool IsLeftClicked = false;
glm::mat4 View;
glm::mat4 Model;

glm::vec4 LightPos = glm::vec4(0.0f, 2.0f, 2.0f, 1.0f);

void initProgram()
{
	Phandle.init(AO);

	Phandle.printVariables(ATTRIBUTE);
	Phandle.printVariables(UNIFORM);
	//model[0] = ModelHandle(MESH, "./Mesh/bs_ears.obj", true);
	model[0] = new ModelHandle(MESH, "./Mesh/bunny.obj", true);
	//model[0] = ModelHandle(TEAPOT, 10, glm::mat4(1.0));
	model[1] = new ModelHandle(PLANE);

	CamHandle.Init(glm::vec3(0.0f, 0.0f, 2.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	View = CamHandle.GetViewMatrix();
}

void setMatrices(int idx)
{
	Model = glm::mat4(1.0f);
	if (idx == 0) {
		float theta = -(float)PI * 1.0f;
		Model *= glm::scale(vec3(8.0f, 8.0f, 8.0f));
		//Model *= glm::rotate(theta, glm::vec3(0.0f, 1.0f, 0.0f));
		Model *= glm::translate(glm::vec3(0.0f, 0.1f, 0.0f));
	}
	else if (idx == 1) {
		Model *= glm::scale(vec3(8.0f, 8.0f, 8.0f));
	}

	View = CamHandle.GetViewMatrix();
	glm::mat4 view = View * CamHandle.GetRotation();
	glm::mat4 modelView = view * Model;
	Phandle.setParameter("Material.Ka", glm::vec3(0.2f, 0.2f, 0.2f));
	Phandle.setParameter("Material.Kd", glm::vec3(0.3f, 0.9f, 0.3f));
	Phandle.setParameter("Material.Ks", glm::vec3(0.0f, 0.0f, 0.0f));
	Phandle.setParameter("Material.Shineness", 100.0f);

	Phandle.setParameter("Light.Intensity", glm::vec3(0.5f));
	Phandle.setParameter("Light.Position", view*LightPos);

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

	pRenderTech->BeginRenderGBuffer();
	{
		for (int i = 0; i < 2; ++i) {
			setMatrices(i);
			model[i]->render();
		}
	}
	pRenderTech->EndRenderGBuffer();

	pRenderTech->Render();

	glutSwapBuffers();
}

void resize(int w, int h)
{
	Width = w;
	Height = h;
	Near = 1.0f;
	Far = 1000.0f;

	glViewport(0, 0, w, h);
	Projection = glm::perspective(45.0f, (float)Width / (float)Height, Near, Far);

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

void idle(void)
{
	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
	switch (button)
	{

	case GLUT_LEFT_BUTTON:

		switch (state) {
		case GLUT_DOWN:
			IsLeftClicked = true;
			CamHandle.StartRotation(x, y);
			glutIdleFunc(idle);
			break;
		case GLUT_UP:
			IsLeftClicked = false;

			glutIdleFunc(NULL);
			CamHandle.EndRotation();
			break;
		default:
			break;
		}
		break;
	case GLUT_RIGHT_BUTTON:
		switch (state) {
		case GLUT_DOWN:
			CamHandle.StartTraslate(x, y);
			glutIdleFunc(idle);
			break;
		case GLUT_UP:
			glutIdleFunc(NULL);
			CamHandle.EndTranslate();
			break;
		default:
			break;
		}
	default:
		break;
	}
}
void motion(int x, int y)
{
	if (IsLeftClicked)
	{
		CamHandle.Rotation(x, y, Width, Height);
	}
	else
	{
		CamHandle.Traslate(x, y, Width, Height);
	}
}

void mouseWheel(int wheel_number, int direction, int x, int y)
{
	if (direction == 1)
	{
		CamHandle.ZoomIn();
	}
	else
	{
		CamHandle.ZoomOut();
	}

	View = CamHandle.GetViewMatrix();
	glutPostRedisplay();
}

int main(int argc, char* argv[])
{
	// NOTE:Should create window before glewInit
	glutInit(&argc, argv);
	glutInitWindowPosition(0, 0);

	glutInitWindowSize(960, 540);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("GLEW");
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutKeyboardFunc(key);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutMouseWheelFunc(mouseWheel);
	Ghandle.init();
	initProgram();
	glutMainLoop();
	return 0;
}