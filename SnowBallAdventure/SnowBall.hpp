# pragma once
# include "Common.hpp"

class SnowBall {

private :
	Vec2 pos;
	Vec2 velocity{ 0, 0 };
	double radius = 32.0;
	bool is_thrown = false;

public :

	SnowBall(const Vec2& pos)
		: pos { pos } { }

	void grow() {
		if (not is_thrown && KeySpace.down()) {
			radius++;
		}
	}

	void throwBail(const Vec2& mousePos) {
		if (not is_thrown) {
			// 投げる方向を設定
			Vec2 direction = (mousePos - pos).normalized();
			velocity = direction * (radius * 2.0); // 半径に応じた速度
			is_thrown = true;
		}
	}

	void update() {
		if (is_thrown) {
			pos += velocity;

			const Rect window_rect { 0,0,WINDOW_SIZE.x,WINDOW_SIZE.y };

			if (window_rect.contains(pos)) {
				reset();
			}
		}
	}
	// 雪玉のリセット
	void reset() {
		radius = 32.0;
		is_thrown = true;
	}

	// 雪玉が投げられたかどうかを確認
	bool hasBeenThrown() const {
		return is_thrown;
	}
	// 雪玉の描画
	void draw() const {
		if (is_thrown) {
			TextureAsset(U"snowBall")(0, 0, 32, 32).scaled(1.4).drawAt(pos);
		}
	}
};
