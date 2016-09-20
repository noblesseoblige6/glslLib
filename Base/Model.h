#pragma once

enum MODEL_TYPE{
	PLANE = 0,
	TORUS = 1,
	CUBE = 2,
	TEAPOT = 3,
	MESH = 4
};
class Model
{
public:
	Model(void);
	~Model(void);
	virtual void render() const = 0;
};

