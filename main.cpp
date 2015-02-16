#include <iostream>

#include "programHandle.h"
#include "glHandle.h"

int main(int argc, char* argv[])
{
	//tmp code
	//has to create window before glewInit
	glutInit(&argc,argv);
	glutInitWindowPosition(100, 100);

	glutInitWindowSize(100, 100);
	glutInitDisplayMode(GLUT_RGBA| GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("GLEW");

	glHandle gh;
	gh.init();

	programHandle ph;
	ph.loadShader("FrasnelReflect.vs", GLSL_SHADER::VERTEX);
	ph.loadShader("FrasnelReflect.fs", GLSL_SHADER::FRAGMENT);
	ph.linkProgram();
	ph.useProgram();

	return 0;
}

