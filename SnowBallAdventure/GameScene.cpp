#include "GameScene.hpp"

GameScene::GameScene(const InitData& init)
	: IScene{ init }
	{
		stopwatch.start();
	}

void GameScene::update() {

	//ゲームがスタートされてない かつ ストップウォッチがスタートされてない
	if (not game_start && not stopwatch.isRunning()) {
		stopwatch.start();
	}
	//ストップウォッチのみがスタートされている(カウントダウン中)
	else if (not game_start) {
		int remaining_time = (4 - stopwatch.s());
		if (remaining_time <= 0) {
			game_start = true;
		}
	}
	//ゲーム中
	else {
		accumulator += Scene::DeltaTime();
		if (char_img_chang_time <= accumulator) {
			accumulator -= char_img_chang_time;
			char_img_index++;
			if (char_img_index == 3) {
				char_img_index = 0;
			}
		}
		TextureAsset(U"x-mas-player-1")(char_img_index * 32,64,32,32).scaled(1.2).drawAt(60, 400);
	}
}

void GameScene::draw() const {

	if (game_start) {

	}
	else {
		int remaining_time = (3 - stopwatch.s());
		String remaining_text = (remaining_time <= 0) ? U"Start!!" : ToString(remaining_time);
		FontAsset(U"bit-big")(remaining_text).drawAt(Scene::Center(),Palette::White);
	}
}
