#include "Shader.h"
using namespace std;
void Shader::Load(std::string fileName)
{
	ifstream myFile;
	myFile.open(SHADER_PATH + fileName);
	if (myFile.fail()) {
		cerr << "Error - failed to open " << fileName << endl;
	}
	string fileText = "";
	string line = "";
	while (getline(myFile, line)) {
		fileText += line + '\n';
	}

	myFile.close();
	m_code = fileText;

	switch (m_type) {
		case VERTEX: {
			m_id = glCreateShader(GL_VERTEX_SHADER);
			break;
		} 
		case FRAGMENT: {
			m_id = glCreateShader(GL_FRAGMENT_SHADER);
			break;
		}
		case TESSELLATION_CONTROL: {
			m_id = glCreateShader(GL_TESS_CONTROL_SHADER);
			break;
		}		
		case TESSELLATION_EVALUATION: {
			m_id = glCreateShader(GL_TESS_EVALUATION_SHADER);
			break;
		}
		case GEOMETRY: {
			m_id = glCreateShader(GL_GEOMETRY_SHADER);
			break;
		}
								
	}

	const char* source = m_code.c_str();
	glShaderSource(m_id, 1, &source, NULL);

	glCompileShader(m_id);
}

Shader::Shader(std::string fileName, ShaderType shaderType)
{
	m_type = shaderType;
	Load(fileName);
}

Shader::~Shader()
{
}
void Shader::LoadFrom(std::string fileName, ShaderType shaderType)
{
	m_type = shaderType;
	Load(fileName);
}

std::string Shader::GetCode()
{
	return m_code;
}
