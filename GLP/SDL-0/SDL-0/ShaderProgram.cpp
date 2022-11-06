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

void ShaderProgram::setFloat(const GLchar* name, GLfloat value)
{
	glUniform1f(glGetUniformLocation(m_id, name), value);
}
void ShaderProgram::setInteger(const GLchar* name, GLint value)
{
	glUniform1i(glGetUniformLocation(m_id, name), value);
}
void ShaderProgram::setVector2f(const GLchar* name, GLfloat x, GLfloat y)
{
	glUniform2f(glGetUniformLocation(m_id, name), x, y);
}
void ShaderProgram::setVector2f(const GLchar* name, const Vector2& value)
{
	glUniform2f(glGetUniformLocation(m_id, name), value.x, value.y);
}
void ShaderProgram::setVector3f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z)
{
	glUniform3f(glGetUniformLocation(m_id, name), x, y, z);
}
void ShaderProgram::setVector3f(const GLchar* name, const Vector3& value)
{
	glUniform3f(glGetUniformLocation(m_id, name), value.x, value.y, value.z);
}
void ShaderProgram::setVector4f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	glUniform4f(glGetUniformLocation(m_id, name), x, y, z, w);
}
void ShaderProgram::setVector4f(const GLchar* name, const Vector4& value)
{
	glUniform4f(glGetUniformLocation(m_id, name), value.x, value.y, value.z, value.w);
}
void ShaderProgram::setMatrix4(const GLchar* name, const Matrix4& matrix)
{
	glUniformMatrix4fv(glGetUniformLocation(m_id, name), 1, GL_FALSE, matrix.getAsFloatPtr());
}
void ShaderProgram::setMatrix4Row(const GLchar* name, const Matrix4Row& matrix)
{
	glUniformMatrix4fv(glGetUniformLocation(m_id, name), 1, GL_FALSE, matrix.getAsFloatPtr());
}
