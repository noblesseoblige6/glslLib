#pragma once
#include <glm/glm.hpp>
#include "Model.h"

class VBOTeapot : public Model
{
private:
	int m_grid;
	glm::mat4 m_lidTransform;

	unsigned int vaoHandle;
	unsigned int faces;

	void generatePatches(float * v, float * n, float *tc, unsigned int* el, int grid);
	void buildPatchReflect(int patchNum,
		float *B, float *dB,
		float *v, float *n, float *, unsigned int *el,
		int &index, int &elIndex, int &, int grid,
		bool reflectX, bool reflectY);
	void buildPatch(glm::vec3 patch[][4],
		float *B, float *dB,
		float *v, float *n,float *, unsigned int *el,
		int &index, int &elIndex, int &, int grid, glm::mat3 reflect, bool invertNormal);
	void getPatch( int patchNum, glm::vec3 patch[][4], bool reverseV );

	void computeBasisFunctions( float * B, float * dB, int grid );
	glm::vec3 evaluate( int gridU, int gridV, float *B, glm::vec3 patch[][4] );
	glm::vec3 evaluateNormal( int gridU, int gridV, float *B, float *dB, glm::vec3 patch[][4] );
	void moveLid(int,float *,glm::mat4);

public:
	VBOTeapot(int grid, glm::mat4 lidTransform);
	void getParam(int& _grid, glm::mat4 _lidTransform);

	void render() const;
};


