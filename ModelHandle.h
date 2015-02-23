#pragma once
#include <string>

#include <glm/glm.hpp>

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
	ModelHandle(MODEL_TYPE, int, glm::mat4);
	~ModelHandle(void);
	void setPram(float, float, int, int);
	void setPram(int, glm::mat4);
	void render() const;
};

