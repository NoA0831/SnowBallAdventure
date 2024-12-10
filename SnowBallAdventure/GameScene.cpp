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
		score_timer += Scene::DeltaTime();
		snow_effect_timer += Scene::DeltaTime();

		player.update();
		snowBall.update();
		effect.update();

		if (KeySpace.down()) {
			snowBall.throwBail(Cursor::Pos());
		}
		//雪エフェクトを0.秒ごとに発生させる
		if (SNOW_EFFECT_SPOWN_TIME <= snow_effect_timer) {
			effect.add<SnowEffect>(
				Vec2{ Random(0,WINDOW_SIZE.y),-100 },
				Size{ 4,4 }
			);
			snow_effect_timer -= SNOW_EFFECT_SPOWN_TIME;
		}
		//スコアを増加させる
		if (SCORE_INCRMENT_TIME <= score_timer) {
			if (score <= 99999) {
				score++;
			}
			score_timer -= SCORE_INCRMENT_TIME;
		}
	}
}

void GameScene::draw() const {

	if (game_start) {
		player.draw();
		snowBall.draw();

		//プレイヤーの残りHPをハートで描画
		{
			const Vec2 start_pos{ 50,27 };
			const int heart_spacing = 20.0;

			const int hp = player.getHp();
			const int max_hp = player.getMaxHp();
			const int has_half_heart = (player.getHp() % 2 == 1);

			for (int i = 0; i < (player.getMaxHp() +1) / 2; ++i) {
				Vec2 pos = start_pos.movedBy(i * heart_spacing, 0);

				if (i < hp / 2) {
					TextureAsset(U"heart_max").scaled(0.8).drawAt(pos);
				}
				else if (i == hp / 2 && hp % 2 == 1) {
					TextureAsset(U"heart_half").scaled(0.8).drawAt(pos);
				}
				else {
					TextureAsset(U"heart_empty").scaled(0.8).drawAt(pos);
				}
			}
			FontAsset(U"bit-mini")(U"HP:").drawAt(25,25,Palette::White);
		}
		//スコアを描画
		//四桁で足りないところはゼロ埋めして表示
		{
			FontAsset(U"bit-mini")(U"Score:").drawAt(40, 50, Palette::White);
			FontAsset(U"bit-mini")(U"{:0>5}"_fmt(ToString(score))).drawAt(95, 50, Palette::White);
		}
		//雪の積もった地面を描画
		//将来的にはプレイヤーの動きと一緒ん動かして疾走感がでるようにしたい
		{
			const int tile_size = 64;
			const int num_tiles = Scene::Width() / tile_size + 1;
			const int ground_y = Scene::Height() - tile_size;

			for (int i = 0; i < num_tiles; i++) {
				TextureAsset(U"grand-snow").draw(i * tile_size,ground_y);
			}
		}
	}
	else {
		int remaining_time = (3 - stopwatch.s());
		String remaining_text = (remaining_time <= 0) ? U"Start!!" : ToString(remaining_time);
		FontAsset(U"bit-big")(remaining_text).drawAt(Scene::Center(),Palette::White);
	}
}
