#pragma once
#include "Common.hpp"

struct StarEffect : IEffect {

	Vec2 pos;
	double speed_x;

	explicit StarEffect(const Vec2 pos)
		: pos{ pos }
	{
		speed_x = Random(0.5, 0.8);
	}

	bool update(double t) override {
		//プレイヤーが走っている感じを出すため、X軸をマイナス方向に向かって移動
		pos.x -= speed_x;
		TextureAsset(U"yellow_star").drawAt(pos);

		if (pos.x < -32) {
			return false;
		}
		return true;
	}
};
