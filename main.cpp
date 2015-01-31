#include <iostream>

#include "programHandle.h"

int main(int argc, char* argv[])
{
	//tmp code
	//has to create window before glewInit
	glutInit(&argc,argv);
	glutInitWindowPosition(100, 100);

	glutInitWindowSize(100, 100);
	glutInitDisplayMode(GLUT_RGBA| GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("GLEW");

	int err = glewInit();
	if (err != GLEW_OK){
		std::cout<<glewGetErrorString(err)<<std::endl;
		exit(1);
	}

	programHandle ph;
	ph.loadShader("FrasnelReflect.vs", GLSL_SHADER::VERTEX);
}