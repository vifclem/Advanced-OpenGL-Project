#pragma once
#include "BaseScene.h"
#include "ScreensaverScene.h"

enum SceneID {
	BASE_SCENE,
	DEMO_SCENE,
	TESSELLATION,
	GEOMETRY,
	MIP_MAP
};

Scene* SceneSelector(SceneID id) {
	switch (id) {
	case BASE_SCENE: {
		return new BaseScene();
		break;
	}	
	case DEMO_SCENE: {
		return new ScreensaverScene();
		break;
	}
	case TESSELLATION: {
		break;
	}
	case GEOMETRY: {
		break;
	}
	case MIP_MAP: {
		break;
	}
	default: {
		return nullptr;
	}
	}
}