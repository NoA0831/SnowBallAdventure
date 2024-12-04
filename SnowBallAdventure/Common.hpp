//Siv3D v0.6.14
#pragma once
#include <Siv3D.hpp>

const Size WINDOW_SIZE{ 500,500 };
const String WINDOW_TITLE = U"";

enum class State
{
	Title,
	Game,
	Result,
	Config
};

struct GameData  {

};

using App = SceneManager<State, GameData>;
