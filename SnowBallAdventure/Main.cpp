#pragma once
#include "Common.hpp"
#include "GameScene.hpp"
#include "TitleScene.hpp"

void Main() {

	Window::Resize(WINDOW_SIZE);
	Window::SetTitle(WINDOW_TITLE);

	FontAsset::Register(U"bit-big",100,U"example/font/DotGothic16/DotGothic16-Regular.ttf", FontStyle::Bitmap);
	FontAsset::Register(U"bit-mini", 20, U"example/font/DotGothic16/DotGothic16-Regular.ttf", FontStyle::Bitmap);

	TextureAsset::Register(U"x-mas-player-1", U"imgs/x-mas-player-1.png");

	TextureAsset::Register(U"snowman_red", U"imgs/snowman_red.png");
	TextureAsset::Register(U"snowman_green", U"imgs/snowman_green.png");

	TextureAsset::Register(U"snow_ball", U"imgs/snowball.png");
	TextureAsset::Register(U"grand-snow", U"imgs/grand_snow.png");

	TextureAsset::Register(U"heart_max", U"imgs/heart_max.png");
	TextureAsset::Register(U"heart_half", U"imgs/heart_half.png");
	TextureAsset::Register(U"heart_empty", U"imgs/heart_empty.png");

	TextureAsset::Register(U"blue_star", U"imgs/blue_star.png");
	TextureAsset::Register(U"yellow_star", U"imgs/yellow_star.png");

	TextureAsset::Register(U"green_arrow", U"imgs/green_arrow.png");

	App manager;
	manager.add<TitleScene>(State::Title);
	manager.add<GameScene>(State::Game);

	manager.init(State::Game);

	while (System::Update()){
		if (not manager.update()){
			break;
		}
	}
}
