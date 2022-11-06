#pragma once
#include "TessellationScene.h"


class TessellationModesScene : public TessellationScene
{
public:
	virtual void LoadShaders();
	virtual void CreateShaderPrograms();
public:
	TessellationModesScene();
	~TessellationModesScene() {}
	virtual void SetupScene();
	virtual void UpdateScene();

};

