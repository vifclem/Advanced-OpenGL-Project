#pragma once
#include "Scene.h"
#include "Shapes2D.h"

class TessellationScene : public Scene
{
protected:
	Shader m_vertexShader, m_fragmentShader, m_tessControlShader, m_tessEvalShader, m_geometryShader;
	ShaderProgram m_shaderProgram;
	virtual void LoadShaders();
	virtual void CreateShaderPrograms();
	virtual void VerticeInformationSlicer();
public:
	TessellationScene();
	~TessellationScene() {}
	virtual void SetupScene();
	virtual void UpdateScene();
};

