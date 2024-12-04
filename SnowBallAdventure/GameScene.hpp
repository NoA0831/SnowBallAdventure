# pragma once
# include "Common.hpp"

class GameScene : public App::Scene {

private:

	Stopwatch stopwatch;
	bool game_start = false;
	double accumulator = 0.0;
	double char_img_chang_time = 0.3;
	int char_img_index = 0;

public:

	GameScene(const InitData& init);

	void update() override;

	void draw() const override;

};
