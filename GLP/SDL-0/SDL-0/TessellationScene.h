#pragma once
#include "Scene.h"
#include "Shapes2D.h"

class TessellationScene : public Scene
{
private:
	Shader m_vertexShader, m_fragmentShader, m_tessControlShader, m_tessEvalShader, m_geometryShader;
	ShaderProgram m_shaderProgram;
	void LoadShaders();
	void CreateShaderPrograms();
	void VerticeInformationSlicer();
public:
	TessellationScene();
	void SetupScene();
	void UpdateScene();
};

