#pragma once
#include "Model.h"

class VBOPlane : public Model
{
private:
	float m_xsize;
	float m_zsize;
	int m_xdivs;
	int m_zdivs;

	unsigned int vaoHandle;
	 int faces;
public:
	VBOPlane(float, float, int, int);
	~VBOPlane(void);
	void getParam(float& _xsize, float& _zsize, int& _xdivs, int& _zdivs);
	void render() const;
};

