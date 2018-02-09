#include "TileSystem.h"



TileSystem::TileSystem() {


	const int WIDTH = 64;
	
	int level[WIDTH*WIDTH];

	for (int i = 0; i < WIDTH*WIDTH; i++) {
		level[i] = 5;
	}
	
	// create the tilemap from the level definition

	map[0].load("textures/tileset.png", sf::Vector2u(32, 32), sf::Vector2i(32, 32), 0, level, WIDTH);
	map[1].load("textures/tileset.png", sf::Vector2u(32, 32), sf::Vector2i(32, 32), 1, level, WIDTH);
	map[2].load("textures/tileset.png", sf::Vector2u(32, 32), sf::Vector2i(32, 32), 2, level, WIDTH);

}


TileSystem::~TileSystem() {
}

void TileSystem::load() {
}

void TileSystem::draw(SpriteBatch &batch) {
	
	for (TileMap &m : map) {
		
		for (GameObject &d : m.getRows()) {
			batch.QueueObject(&d);
		}

	}
}

