#pragma once
#include "Common.hpp"

struct SnowEffect : IEffect {

	Vec2 pos;
	Size size;
	ColorF color;

	double speed_y;   //垂直方向の速度
	double base_x;    //水平位置の基準値
	double amplitude; //揺れの振幅
	double phase;     //揺れの初期位相

	explicit SnowEffect(const Vec2& pos,const Size& size)
		: pos { pos },
		size { size }
	{
		base_x = pos.x;
		speed_y = Random(2.0, 5.0);
		amplitude = Random(10.0, 20.0);
		phase = Random(0.0, Math::TwoPi);
		color = HSV(Random(200.0, 240.0), 0.2, Random(0.8, 1.0));
	}

	bool update(double t) override {
		//Y座標を単調に増加
		pos.y += speed_y;
		//Sin波を用いて水平位置を更新
		pos.x = base_x + amplitude * Math::Sin( Scene::Time() * 2.0 + phase);
		//徐々に透明に
		//color.a = 1.0 - (t / 2.0);

		if (pos.y > Scene::Height()) {
			return true;
		}
		RectF{ pos.movedBy(1,1),size }.draw(Palette::Gray);
		RectF{ pos,size }.draw(color);
	}
};
