#pragma once
#include "Common.hpp"
#include "GameScene.hpp"
#include "TitleScene.hpp"

void Main() {

	Window::Resize(WINDOW_SIZE);
	Window::SetTitle(WINDOW_TITLE);

	FontAsset::Register(U"bit-big",100,U"example/font/DotGothic16/DotGothic16-Regular.ttf", FontStyle::Bitmap);
	TextureAsset::Register(U"x-mas-player-1", U"imgs/x-mas-player-1.png");

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
