#pragma once
#include "Model.h"

class VBOCube: public Model
{
private:
	unsigned int vaoHandle;

public:
	VBOCube();
	void render() const;
};
