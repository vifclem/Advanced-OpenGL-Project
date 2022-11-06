#pragma once
#include "Scene.h"
#include "ShaderProgram.h"
#include "Shapes2D.h"

class ScreensaverScene : public Scene
{
private:
	Shader m_vertexShader, m_fragmentShader;
	ShaderProgram m_shaderProgram;
	void LoadShaders();
	void CreateShaderPrograms();
	void VerticeInformationSlicer();
public:
	ScreensaverScene();
	~ScreensaverScene() {}
	void SetupScene();
	void UpdateScene();
};

