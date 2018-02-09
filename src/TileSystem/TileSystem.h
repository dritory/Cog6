#pragma once
#include "TileMap.h"
class TileSystem {
public:
	TileSystem();
	~TileSystem();

	void load();

	void draw(sf::RenderWindow &window);

	static const unsigned int HEIGHT = 10;

private:
	// define the level with an array of tile indices
	TileMap map[HEIGHT];

	const int NONCOLLISION_TILES[1] = {0};
	int foo = 0;
};

