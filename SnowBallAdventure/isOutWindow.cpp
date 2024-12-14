#pragma once
#include "Common.hpp"

static bool isOutWindow(const Vec2& pos) {

	if (0 > pos.x || pos.x > Scene::Width() || 0 > pos.y || pos.y > Scene::Height()) {
		return true;
	}
	return false;
}
