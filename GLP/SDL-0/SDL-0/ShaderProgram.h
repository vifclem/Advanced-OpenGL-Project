#pragma once
#include "Shader.h"
#include <vector>
#include <Matrix4.h>
#include <Vector2.h>
#include <Matrix4Row.h>

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
	void setFloat(const GLchar* name, GLfloat value);
	void setInteger(const GLchar* name, GLint value);
	void setVector2f(const GLchar* name, GLfloat x, GLfloat y);
	void setVector2f(const GLchar* name, const Vector2& value);
	void setVector3f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z);
	void setVector3f(const GLchar* name, const Vector3& value);
	void setVector4f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
	void setVector4f(const GLchar* name, const Vector4& value);
	void setMatrix4(const GLchar* name, const Matrix4& matrix);
	void setMatrix4Row(const GLchar* name, const Matrix4Row& matrix);
};

