#include "ModelHandle.h"
using std::string;

ModelHandle::ModelHandle()
{
model = NULL;
}
ModelHandle::ModelHandle(MODEL_TYPE type)
{
	switch(type){
	case TORUS:
		model = new VBOTorus(1.0f, 0.5f, 50, 50);
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
	default:
		model = NULL;
		break;
	}
}


ModelHandle::~ModelHandle(void)
{
	delete model;
}

void ModelHandle::setPram(float outerRadius, float innerRadius, int nsides, int nrings)
{
	model = new VBOTorus(outerRadius, innerRadius, nsides, nrings);
}

void ModelHandle::render() const
{
	if(model == NULL){
		printf("No model data!\n");
		return;
	}
	model->render();
}