#pragma once
#include "Model.h"

class VBOPlane : public Model
{
private:
	unsigned int vaoHandle;
	 int faces;
public:
	VBOPlane(float, float, int, int);
	~VBOPlane(void);
void render() const;
};

