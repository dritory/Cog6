#pragma once

#include "TileSystem\TileSystem.h"


class Game {
public:
	Game();
	~Game();

	void Start();

private:
	TileSystem tileSystem;
};

