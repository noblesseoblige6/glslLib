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
	ModelHandle(const ModelHandle&);
	ModelHandle(MODEL_TYPE);
	ModelHandle(MODEL_TYPE, float, float, int, int);
	ModelHandle(MODEL_TYPE, int, glm::mat4);
	ModelHandle(MODEL_TYPE, const std::string&, bool);
	~ModelHandle(void);
	void setPram(float, float, int, int);
	void setPram(int, glm::mat4);
	void render() const;
	ModelHandle& operator=(const ModelHandle&);
};

