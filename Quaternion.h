#pragma once
#include <glm/glm.hpp>

class Quaternion
{
public:
	Quaternion();
	~Quaternion();

	void Init();

	void QuatMul(const glm::vec4& dQuat);

	void QuatRot();

	void StartRotation(int x, int y);

	void EndRotation();

	void Rotation(int x, int y, int w, int h);

	const glm::mat4& GetRotation() { return rotation; }

private:
	int curx;
	int cury;

	glm::vec4 savedQuat;
	glm::vec4 curQuat;
	glm::mat4 rotation;
};
