#pragma once
#include "Common.hpp"

class SnowBall {
private:
	Vec2 pos;                     // 雪玉の位置
	Vec2 velocity;			      // 雪玉の速度
	double gravity = 1.2;         // 重力
	double power = 0;             // 攻撃力

public:
	SnowBall(const Vec2& pos,const double& power,const Vec2& velocity)
		: pos{ pos },
		power { power },
		velocity { velocity }{}


	// 雪玉の更新処理
	void update() {
		velocity.y += gravity; // 重力を適用
		pos += velocity;
	}

	// 現在の位置を取得
	Vec2 getPos() const {
		return pos;
	}

	// 雪玉の描画
	void draw() const {
		TextureAsset(U"snow_ball").drawAt(pos);
	}
};
