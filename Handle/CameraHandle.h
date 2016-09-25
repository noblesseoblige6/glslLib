#pragma once
#include<glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../Quaternion.h"

class CameraHandle
{
public:
	CameraHandle() {}
	~CameraHandle();

	void Init(const glm::vec3 _cameraPos, const glm::vec3 _cameraDir, const glm::vec3 _cameraUp){
		m_curx = 0;
		m_cury = 0;
		
		m_cameraPos = _cameraPos;
		m_cameraDir = _cameraDir;
		m_cameraUp  = _cameraUp;
		
		m_quat.Init();
	}


	void StartTraslate(int x, int y) 
	{
		m_curx = x;
		m_cury = y;
	}
	void EndTranslate() {}

	void Traslate(int x, int y, int width , int height) 
	{
		float dx = (x - m_curx) / (float)width;
		float dy = -(y - m_cury) / (float)height;

		glm::vec3 d = glm::vec3(dx)*glm::cross(m_cameraDir - m_cameraPos, m_cameraUp) + glm::vec3(dy)*m_cameraUp;
		m_cameraPos += d;
		m_cameraDir += d;
	}

	void StartRotation(int x, int y)
	{
		m_quat.StartRotation(x, y);
	}

	void EndRotation()
	{
		m_quat.EndRotation();
	}

	void Rotation(int x, int y, int w, int h)
	{
		m_quat.Rotation(x, y, w, h);
	}

	void ZoomIn()
	{
		m_cameraPos += glm::vec3(0.25f) * (m_cameraDir - m_cameraPos);
	}
	
	void ZoomOut()
	{
		m_cameraPos += glm::vec3(0.25f) * (m_cameraPos - m_cameraDir);
	}

	const glm::mat4& GetRotation() { return m_quat.GetRotation(); }
	glm::mat4 GetViewMatrix() { return glm::lookAt(m_cameraPos, m_cameraDir, m_cameraUp); }

private:
	int m_curx;
	int m_cury;

	glm::vec3 m_cameraPos;
	glm::vec3 m_cameraDir;
	glm::vec3 m_cameraUp;

	Quaternion m_quat;	
};

