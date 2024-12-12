#pragma once
#include "Common.hpp"

class SnowBall {
private:
	Vec2 pos;                     // 雪玉の位置
	Vec2 velocity{ 0, 0 };        // 雪玉の速度
	double radius = 32.0;         // 雪玉の半径
	bool is_thrown = false;       // 雪玉が投げられているかどうか
	double gravity = 0.5;         // 重力

public:
	SnowBall(const Vec2& pos)
		: pos{ pos } { }

	// 雪玉を成長させる
	void grow() {
		if (not is_thrown) {
			radius = Min(radius + 0.5, 64.0); // 最大サイズを64に制限
		}
	}

	// 雪玉を投げる
	void throwBall(const Vec2& direction) {
		if (not is_thrown) {
			velocity = direction * (radius * 1.5); // 方向と半径に基づいた速度
			is_thrown = true;
		}
	}

	// 雪玉の更新処理
	void update() {
		if (is_thrown) {
			velocity.y += gravity; // 重力を適用
			pos += velocity;

			// 雪玉が画面外に出たらリセット
			if (pos.y > Scene::Height() || pos.x < 0 || pos.x > Scene::Width()) {
				reset();
			}
		}
	}

	// 雪玉のリセット
	void reset() {
		radius = 32.0;          // 半径をリセット
		is_thrown = false;      // 状態をリセット
		velocity = Vec2{ 0, 0 };
	}

	// 雪玉が投げられているか
	bool hasBeenThrown() const {
		return is_thrown;
	}

	// 現在の位置を取得
	Vec2 getPosition() const {
		return pos;
	}

	// 現在の半径を取得
	double getRadius() const {
		return radius;
	}

	// 雪玉の描画
	void draw() const {
		Circle{ pos, radius }.draw(Palette::White);
	}
};
