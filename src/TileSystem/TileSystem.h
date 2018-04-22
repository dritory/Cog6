#pragma once
#include "TileMap.h"
#include "..\Rendering\SpriteBatch.h"
#include "../EntitySystem/Pathfinder.h"

class TileSystem {
public:
	TileSystem();
	~TileSystem();

	void load();


	void LateUpdate();
	void draw(SpriteBatch &batch);

	bool canWalkHere(int x, int y, int z);

	bool canWalkHere(sf::Vector3i pos);
	int getTileId(int x, int y, int z);
	int getTileId(sf::Vector3i pos);

	void setTileId(sf::Vector3f pos, int id);
	void setTileId(int x, int y, int z, int id);


	sf::Vector2i worldToTileCoord(sf::Vector3f pos);

	sf::Vector2i isoToTileCoord(sf::Vector3f pos);

	sf::Vector3f tileToIsoCoord(sf::Vector3i pos);

	TileMap &getMap(unsigned int y);

	Pathfinder pathfinder;

	static const unsigned int HEIGHT = 10;

private:
	// define the level with an array of tile indices
	TileMap map[HEIGHT];

	const int NONCOLLISION_TILES[1] = {0};
	
	 int WIDTH = 512;
	int foo = 0;
};

