#pragma once
#include "Shader.h"

class ShaderProgram
{
private:
	unsigned int m_id;
	unsigned m_vert;
	unsigned m_frag;

public:
	ShaderProgram();
	ShaderProgram(Shader& vertP, Shader& fragP);
	~ShaderProgram();

	void GenerateFrom(Shader& vertP, Shader& fragP);

	unsigned int GetID();
	void Use();
};

