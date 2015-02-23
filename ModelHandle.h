#pragma once
#include <string>
#include "Model.h"

class ModelHandle
{
private:
	Model* model;
public:
	ModelHandle(void);
	ModelHandle(MODEL_TYPE);
	ModelHandle(MODEL_TYPE, const std::string&, bool);
	ModelHandle(MODEL_TYPE, float, float, int, int);
	~ModelHandle(void);
	void setPram(float, float, int, int);
	void render() const;
};

