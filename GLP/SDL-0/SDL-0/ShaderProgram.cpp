#include "ShaderProgram.h"

ShaderProgram::ShaderProgram()
{
	m_id = 0;
}

ShaderProgram::ShaderProgram(Shader& vertP, Shader& fragP)
{
	m_id = glCreateProgram();
	//now attach shaders to use to the program
	m_vert = vertP.GetID();
	m_frag = fragP.GetID();
	glAttachShader(m_id, vertP.GetID());
	glAttachShader(m_id, fragP.GetID());
	//and link it
	glLinkProgram(m_id);
}

ShaderProgram::~ShaderProgram()
{
}

void ShaderProgram::Compose(Shader& vertP, Shader& fragP)
{
	m_id = glCreateProgram();
	//now attach shaders to use to the program
	m_vert = vertP.GetID();
	m_frag = fragP.GetID();
	glAttachShader(m_id, vertP.GetID());
	glAttachShader(m_id, fragP.GetID());
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
