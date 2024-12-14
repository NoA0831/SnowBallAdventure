# pragma once
# include "Common.hpp"
# include "Player.hpp"
# include "isOutWindow.cpp"
# include "SnowBall.hpp"
# include "SnowEffect.hpp"
# include "StarEffect.hpp"

class GameScene : public App::Scene {

private:
	Effect effect;
	Effect star_effect;
	Stopwatch stopwatch;
	Array<SnowBall> snow_balls;
	bool game_start = false;
	Player player { Vec2{ 60,412}};
	int score = 0;
	
	double score_timer = 0.0;
	double snow_effect_timer = 0.0;
	double star_effect_timer = 0.0;
	double snow_ball_throw_timer = 0.0;

	const double INCREMENT_POWER = 0.05;
	const double MAX_SNOW_BALL_THROW_POWER = 3.0;
	const double MIN_SNOW_BALL_THROW_POWER = 1.2;

	const int MAX_SNOW_BALL_NUM = 5;
	const int MAX_STAR_EFFECT_NUM = 6;

	const double CAN_THROW_MIN_ANGLE = -60_deg;
	const double CAN_THROW_MAX_ANGLE = -5_deg;

	const double STAR_EFFECT_SPOWN_TIME = 5.0;
	const double SCORE_INCRMENT_TIME = 0.5;
	const double SNOW_EFFECT_SPOWN_TIME = 0.08;

	double snow_ball_throw_power = MIN_SNOW_BALL_THROW_POWER;
	double snow_ball_throw_angle = 0.0;

public:

	GameScene(const InitData& init);

	void update() override;

	void draw() const override;

};
