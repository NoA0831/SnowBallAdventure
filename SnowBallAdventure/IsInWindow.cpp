#pragma once
#include "Common.hpp"

static bool isInWindow(const Vec2& pos) {

	if (0 > pos.x || pos.x > WINDOW_SIZE.x || 0 > pos.y || pos.y > WINDOW_SIZE.y) {
		return false;
	}
	return false;
}
