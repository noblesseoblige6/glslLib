#include "ModelHandle.h"
#include "VBOPlane.h"
#include "VBOTorus.h"
#include "VBOCube.h"
#include "VBOTeapot.h"
#include "VBOMesh.h"

#include <typeinfo>

using std::string;

ModelHandle::ModelHandle()
{
model = NULL;
}
ModelHandle::ModelHandle(MODEL_TYPE type)
{
	switch(type){
	case PLANE:
		model = new VBOPlane(1.0f, 1.0f, 20, 20);
		break;
	case TORUS:
		model = new VBOTorus(1.0f, 0.5f, 50, 50);
		break;
	case CUBE:
		model = new VBOCube();
		break;
	case TEAPOT:
		model = new VBOTeapot(10, glm::mat4(1.0f));
		break;
	default:
		model = NULL;
		break;

	}
}
ModelHandle::ModelHandle(MODEL_TYPE type, const string& path, bool center)
{
	switch(type){
	case MESH:
		model = new VBOMesh(path.c_str(), center);
		break;
	default:
		model = NULL;
		break;
	}
}
ModelHandle::ModelHandle(MODEL_TYPE type, float outerRadius, float innerRadius, int nsides, int nrings)
{
	switch(type){
	case TORUS:
		model = new VBOTorus(outerRadius, innerRadius, nsides, nrings);
		break;
		case PLANE:
		model = new VBOPlane(outerRadius, innerRadius, nsides, nrings);
		break;
	default:
		model = NULL;
		break;
	}
}

ModelHandle::ModelHandle(MODEL_TYPE type, int grid, glm::mat4 lidTransform)
{
	switch(type){
	case TEAPOT:
		model = new VBOTeapot(grid, lidTransform);
		break;
	default:
		model = NULL;
		break;
	}
}

ModelHandle::~ModelHandle(void)
{
	delete model;
}

void ModelHandle::setPram(float f, float g, int n, int m)
{	
	if(typeid (VBOPlane) == typeid (*model)){
		model = new VBOPlane(f, g, n, m);
	}
	else if(typeid (VBOTorus) == typeid (*model)){
		model = new VBOTorus(f, g, n, m);
	}
	else{
		printf("Type Error! Check parameters\n");
	}
}

void ModelHandle::setPram(int grid, glm::mat4 lidTransform)
{
	if(typeid (VBOTeapot) == typeid (*model)){
		model = new VBOTeapot(grid, lidTransform);
	}
	else{
		printf("Type Error! Check parameters\n");
	}
}

void ModelHandle::render() const
{
	if(model == NULL){
		printf("No model data!\n");
		return;
	}
	model->render();
}