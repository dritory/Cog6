#pragma once
#include "TileMap.h"
#include "..\Rendering\SpriteBatch.h"
class TileSystem {
public:
	TileSystem();
	~TileSystem();

	void load();

	void draw(SpriteBatch &batch);

	static const unsigned int HEIGHT = 10;

private:
	// define the level with an array of tile indices
	TileMap map[HEIGHT];

	const int NONCOLLISION_TILES[1] = {0};
	int foo = 0;
};

