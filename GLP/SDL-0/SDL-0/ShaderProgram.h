#pragma once
#include "Shader.h"
#include <vector>

class ShaderProgram
{
private:
	unsigned int m_id;

public:
	ShaderProgram();
	~ShaderProgram();

	void Compose(std::vector<Shader*> shaders);

	unsigned int GetID();
	void Use();
};

