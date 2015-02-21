#pragma once

enum MODEL_TYPE{
TORUS = 0,
MESH = 1
};
class Model
{
public:
	Model(void);
	~Model(void);
	virtual void render() const = 0;
};

