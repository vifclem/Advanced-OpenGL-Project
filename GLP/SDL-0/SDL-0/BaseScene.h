#pragma once
#include "Scene.h"
#include "ShaderProgram.h"
#include "glew.h"
#include <string>


class BaseScene: public Scene
{
private :
	Shader m_rainbowVShader ,m_animatedVShader,m_rainbowFShader;
	ShaderProgram m_simpleProgram, m_animatedProgram;
	void LoadShaders();
	void CreateShaderPrograms();
	void VerticeInformationSlicer();
public:
	BaseScene();
	void SetupScene();
	void UpdateScene();


};