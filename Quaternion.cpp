#include "Quaternion.h"
#include "defines.h"

Quaternion::Quaternion() : curx(0), cury(0), savedQuat(glm::vec4(1.0, 0.0, 0.0, 0.0)), curQuat(glm::vec4(0.0))
{
}

Quaternion::~Quaternion()
{
}

void Quaternion::Init()
{
	curQuat = savedQuat;
	QuatRot();
}

void Quaternion::QuatMul(const glm::vec4& dQuat)
{
	curQuat[0] = dQuat[0] * savedQuat[0] - dQuat[1] * savedQuat[1] - dQuat[2] * savedQuat[2] - dQuat[3] * savedQuat[3];
	curQuat[1] = dQuat[0] * savedQuat[1] + dQuat[1] * savedQuat[0] + dQuat[2] * savedQuat[3] - dQuat[3] * savedQuat[2];
	curQuat[2] = dQuat[0] * savedQuat[2] - dQuat[1] * savedQuat[3] + dQuat[2] * savedQuat[0] + dQuat[3] * savedQuat[1];
	curQuat[3] = dQuat[0] * savedQuat[3] + dQuat[1] * savedQuat[2] - dQuat[2] * savedQuat[1] + dQuat[3] * savedQuat[0];
}

void Quaternion::QuatRot()
{
	double x2 = curQuat[1] * curQuat[1] * 2.0;
	double y2 = curQuat[2] * curQuat[2] * 2.0;
	double z2 = curQuat[3] * curQuat[3] * 2.0;
	double xy = curQuat[1] * curQuat[2] * 2.0;
	double yz = curQuat[2] * curQuat[3] * 2.0;
	double zx = curQuat[3] * curQuat[1] * 2.0;
	double xw = curQuat[1] * curQuat[0] * 2.0;
	double yw = curQuat[2] * curQuat[0] * 2.0;
	double zw = curQuat[3] * curQuat[0] * 2.0;

	rotation[0][0] = 1.0 - y2 - z2; rotation[0][1] = xy + zw;       rotation[0][2] = zx - yw;       rotation[0][3] = 0.0;
	rotation[1][0] = xy - zw;       rotation[1][1] = 1.0 - z2 - x2; rotation[1][2] = yz + xw;       rotation[1][3] = 0.0;
	rotation[2][0] = zx + yw;       rotation[2][1] = yz - xw;       rotation[2][2] = 1.0 - x2 - y2; rotation[2][3] = 0.0;
	rotation[3][0] = 0.0;           rotation[3][1] = 0.0;           rotation[3][2] = 0.0;           rotation[3][3] = 1.0;
}

void Quaternion::StartRotation(int x, int y)
{
	curx = x;
	cury = y;
}

void Quaternion::EndRotation()
{
	savedQuat = curQuat;
}

void Quaternion::Rotation(int x, int y, int w, int h)
{
	double dx = (x - curx) * (1.0 / (double)w);
	double dy = (y - cury) * (1.0 / (double)h);

	double a = sqrt(dx * dx + dy * dy);

	if (a != 0.0) {
		double ar = a * TWOPI * 0.5;
		double as = sin(ar) / a;
		glm::vec4 dQuat = glm::vec4(cos(ar), dy * as, dx * as, 0.0);

		// 回転の初期値 cq に dq を掛けて回転を合成する
		QuatMul(dQuat);

		// クォータニオンから回転の変換行列を求める
		QuatRot();
	}
}