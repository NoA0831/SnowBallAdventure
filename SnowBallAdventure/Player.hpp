#pragma once
#include "Common.hpp"

class Player {

private:

	Vec2 pos;
	Size size;
	int hp;
	double accumulator = 0.0;
	double char_img_chang_time = 0.3;
	int char_img_index = 0;

	const int MAX_HP = 8;

public:

	Player(const Vec2& pos)
		: pos { pos }
		{
			hp = 1;
		}
	void update() {

		accumulator += Scene::DeltaTime();
		if (char_img_chang_time <= accumulator) {
			accumulator -= char_img_chang_time;
			char_img_index++;
			if (char_img_index == 3) {
				char_img_index = 0;
			}
		}
	}
	void draw() const {
		
		TextureAsset(U"x-mas-player-1")(char_img_index * 32, 64, 32, 32).scaled(1.4).drawAt(pos);
	}
	int getHp() const {
		return hp;
	}
	int getMaxHp() const {
		return MAX_HP;
	}
};
