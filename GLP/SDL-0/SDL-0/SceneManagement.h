#pragma once

#include "BaseScene.h"

enum SceneID {
	BASE_SCENE,
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