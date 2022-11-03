#pragma once
#include <string>
#include <vector>
#include "Window.h"
#include "Shader.h"

class Scene
{
protected:
	std::string m_name;
	unsigned int m_vbo, m_vao;
	std::vector<float> m_vertices;

public:
	Scene(std::string nameP = "Demo");
	~Scene(){}
	
	virtual void SetupScene() = 0;
	virtual void UpdateScene() = 0;
};

