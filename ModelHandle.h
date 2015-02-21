#pragma once
#include <string>
#include "Model.h"
#include "vbotorus.h"

class ModelHandle
{
private:
	Model* model;
public:
	ModelHandle(MODEL_TYPE);
	ModelHandle(MODEL_TYPE, const std::string&);
	ModelHandle(MODEL_TYPE, float, float, int, int);
	~ModelHandle(void);
	void setPram(float, float, int, int);
	void render() const;
};

