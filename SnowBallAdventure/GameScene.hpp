# pragma once
# include "Common.hpp"
# include "Player.hpp"
# include "SnowBall.hpp"
# include "SnowEffect.hpp"
# include "StarEffect.hpp"

class GameScene : public App::Scene {

private:
	Effect effect;
	Effect star_effect;
	SnowBall snowBall { Vec2{60,400} };
	Stopwatch stopwatch;
	bool game_start = false;
	Player player { Vec2{ 60,412}};
	int score = 0;

	double score_timer = 0.0;
	double snow_effect_timer = 0.0;
	double star_effect_timer = 0.0;
	double snow_ball_throw_timer = 0.0;

	const int MAX_STAR_EFFECT_NUM = 6;

	const double STAR_EFFECT_SPOWN_TIME = 1.5;
	const double SCORE_INCRMENT_TIME = 0.5;
	const double SNOW_EFFECT_SPOWN_TIME = 0.08;

public:

	GameScene(const InitData& init);

	void update() override;

	void draw() const override;

};
