#pragma once
#include "Model.h"

class VBOTorus: public Model
{
private:
	
	unsigned int vaoHandle;
	int faces, rings, sides;

	void generateVerts(float * , float * ,float *, unsigned int *,
		float , float);

public:
	VBOTorus(float, float, int, int);

	void render() const;
};
