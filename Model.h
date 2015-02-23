#pragma once

enum MODEL_TYPE{
TORUS = 0,
CUBE = 1,
MESH = 2
};
class Model
{
public:
	Model(void);
	~Model(void);
	virtual void render() const = 0;
};

