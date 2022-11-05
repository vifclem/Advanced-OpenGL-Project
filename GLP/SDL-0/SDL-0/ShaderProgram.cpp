#include "ShaderProgram.h"
using namespace std;


ShaderProgram::ShaderProgram()
{
	m_id = 0;
}

ShaderProgram::~ShaderProgram()
{
}

void ShaderProgram::Compose(vector<Shader*> shaders)
{
	m_id = glCreateProgram();
	//now attach shaders to use to the program
	for (int s = 0; s < shaders.size(); s++) {
		glAttachShader(m_id, shaders[s]->GetID());
	}
	//and link it
	glLinkProgram(m_id);
}


unsigned int ShaderProgram::GetID()
{
	return m_id;
}

void ShaderProgram::Use()
{
	glUseProgram(m_id);
}
