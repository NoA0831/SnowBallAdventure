#include "GameScene.hpp"

GameScene::GameScene(const InitData& init)
	: IScene{ init }
	{
		stopwatch.start();
		for (int i = 0; i < MAX_STAR_EFFECT_NUM / 2; i++) {
			star_effect.add<StarEffect>(
			Vec2{ Random(32,Scene::Width() - 32),Random(15,150)}
			);
		}
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
		star_effect_timer += Scene::DeltaTime();

		player.update();
		snowBall.update();
		effect.update();
		star_effect.update();

		if (KeySpace.down()) {
			snowBall.throwBall(Cursor::Pos());
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
		//星エフェクトを定期的に発生
		//表示する星の数はMAXで2コ
		if (STAR_EFFECT_SPOWN_TIME <= star_effect_timer) {
			if (star_effect.num_effects() < MAX_STAR_EFFECT_NUM) {
				star_effect_timer -= STAR_EFFECT_SPOWN_TIME;
				star_effect.add<StarEffect>(
					Vec2{ (Scene::Width()) + 64,Random(15,150) }
				);
			}
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
		//雪玉を投げる方向を示す矢印を描画する
		//投げられない角度の場合は、矢印を上限、または下限で表示する
		{
			Vec2 mouse_pos = Cursor::PosF();
			Vec2 player_pos = player.getPos();

			//プレイヤーの位置からマウスの位置への角度を計算
			double angle = Atan2(
				mouse_pos.y - player_pos.y,
				mouse_pos.x - player_pos.x
			);
			//上限値、下限値より超えてるとどちらかに丸める
			angle = Clamp(angle, CAN_THROW_MIN_ANGLE, CAN_THROW_MAX_ANGLE);

			Vec2 direction = Vec2{ Cos(angle),Sin(angle) };
			Vec2 arrowTip = player_pos + direction * 100;

			TextureAsset(U"green_arrow").rotated(angle).drawAt(player_pos.movedBy(50, 0));
		}
	}
	else {
		int remaining_time = (3 - stopwatch.s());
		String remaining_text = (remaining_time <= 0) ? U"Start!!" : ToString(remaining_time);
		FontAsset(U"bit-big")(remaining_text).drawAt(Scene::Center(),Palette::White);
	}
}
