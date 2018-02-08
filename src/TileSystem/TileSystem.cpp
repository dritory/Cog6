#include "TileSystem.h"



TileSystem::TileSystem() {


	const int WIDTH = 32;
	
	int level[WIDTH*WIDTH];

	for (int i = 0; i < WIDTH*WIDTH; i++) {
		level[i] = 5;
	}
	
	// create the tilemap from the level definition

	map[0].load("assets/textures/tileset.png", sf::Vector2u(32, 32), sf::Vector2i(32, 32), 0, level, WIDTH);
	map[1].load("assets/textures/tileset.png", sf::Vector2u(32, 32), sf::Vector2i(32, 32), 1, level, WIDTH);
	map[2].load("assets/textures/tileset.png", sf::Vector2u(32, 32), sf::Vector2i(32, 32), 2, level, WIDTH);

}


TileSystem::~TileSystem() {
}

void TileSystem::load() {
}

void TileSystem::draw(sf::RenderWindow &window) {
	

	
	
	for (int i = 0; i < 1024; i++) {
		map[2].setTileId(rand() % 32, rand() % 32, 5);
		map[1].setTileId(rand() % 32, rand() % 32, 5);
		map[0].setTileId(rand() % 32, rand() % 32, 5);
	}
	for (TileMap &m : map) {
		
		for (sf::Drawable &d : m.getRows()) {
			window.draw(d);
		}

	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		sf::Vector2i tile = map[2].mouseToTile( map[2], window);
		map[2].setTileId(tile.x, tile.y, 32);
		tile = map[1].mouseToTile( map[1], window);
		map[1].setTileId(tile.x, tile.y, 32);
		tile = map[0].mouseToTile( map[0], window);
		map[0].setTileId(tile.x, tile.y, 32);
		//map[0].sprite.setPosition(map[0].getPosition());
	}
}

