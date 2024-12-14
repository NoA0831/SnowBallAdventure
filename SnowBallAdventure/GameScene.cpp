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
		effect.update();
		star_effect.update();

		for (auto& snow_ball : snow_balls) {
			snow_ball.update();
		}

		//雪玉を投げたらパワーをリセット
		if (KeyEnter.down()&& snow_balls.size() < MAX_SNOW_BALL_NUM) {
			Print << U"throw!!";
			snow_balls.emplace_back(
				player.getPos(),
				snow_ball_throw_power,
				Vec2{
					Cos(snow_ball_throw_angle) * snow_ball_throw_power * 10,
					Sin(snow_ball_throw_angle) * snow_ball_throw_power * 10
				}
			);
			snow_ball_throw_power = MIN_SNOW_BALL_THROW_POWER;
		}
		//雪エフェクトを0.秒ごとに発生させる
		if (SNOW_EFFECT_SPOWN_TIME <= snow_effect_timer) {
			effect.add<SnowEffect>(
				Vec2{ Random(0,WINDOW_SIZE.y),-100 },
				Size{ 2,2 }
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
		//雪玉を投げる角度を計算
		//投げることができる角度まで丸めて計算する
		{
			Vec2 mouse_pos = Cursor::PosF();
			Vec2 player_pos = player.getPos();

			//プレイヤーの位置からマウスの位置への角度を計算
			double angle = Atan2(
				mouse_pos.y - player_pos.y,
				mouse_pos.x - player_pos.x
			);
			//上限値、下限値より超えてるとどちらかに丸める
			snow_ball_throw_angle = Clamp(angle, CAN_THROW_MIN_ANGLE, CAN_THROW_MAX_ANGLE);
		}
		//スペースキーを連打するたびに雪玉を投げる際のパワーが上昇
		if (KeySpace.down() && snow_balls.size() < MAX_SNOW_BALL_NUM) {
			Print << snow_ball_throw_power;

			const double incremented_power = snow_ball_throw_power + INCREMENT_POWER;

			if (incremented_power < MAX_SNOW_BALL_THROW_POWER) {
				snow_ball_throw_power = incremented_power;
			}
		}
		//画面外に出た雪玉を削除
		snow_balls.remove_if([](const SnowBall& snow_ball) {
			return isOutWindow(snow_ball.getPos());
		});
		Console << snow_ball_throw_power;
	}
}

void GameScene::draw() const {

	if (game_start) {
		for (const auto& snow_ball : snow_balls) {
			snow_ball.draw();
		}
		player.draw();

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
		//プレイヤーと干渉するので、X軸方向に+50して描画
		{
			Vec2 pos = player.getPos().movedBy(50, 0);
			TextureAsset(U"green_arrow").rotated(snow_ball_throw_angle).drawAt(pos);
		}
	}
	else {
		int remaining_time = (3 - stopwatch.s());
		String remaining_text = (remaining_time <= 0) ? U"Start!!" : ToString(remaining_time);
		FontAsset(U"bit-big")(remaining_text).drawAt(Scene::Center(),Palette::White);
	}
}
