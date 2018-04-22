#pragma once
#include "TileMap.h"
#include "..\Rendering\SpriteBatch.h"
#include "../EntitySystem/Pathfinder.h"
#include "TileEntity.h"
class TileEntity;

class TileSystem {
public:
	TileSystem(int width, int height, int tileSize = 32);
	~TileSystem();

	void load();


	void LateUpdate();
	void draw(SpriteBatch &batch);

	bool canWalkHere(int x, int y, int z);

	bool canWalkHere(sf::Vector3i pos);

	void setCollision(int x, int y, int z, bool collidable);

	bool isInBounds(int x, int y, int z);

	bool isInBounds(sf::Vector3i pos);

	int getTileId(int x, int y, int z);
	int getTileId(sf::Vector3i pos);

	void setTileId(sf::Vector3f pos, int id);
	void setTileId(int x, int y, int z, int id);

	void setTileEntity(int x, int y, int z, TileEntity *entity);
	TileEntity *getTileEntity(int x, int y, int z);

	sf::Vector2i worldToTileCoord(sf::Vector3f pos);

	sf::Vector2i isoToTileCoord(sf::Vector3f pos);

	sf::Vector3f tileToIsoCoord(sf::Vector3i pos);

	TileMap &getMap(unsigned int y);
	int getHeight() { return height; };
	int getWidth() { return width; };
	int getWidth_world() { return width * tileSize; };
	int getTileSize() { return tileSize; };

	Pathfinder *pathfinder;

	TileEntity **tileEntities;
	
	

private:
	// define the level with an array of tile indices
	TileMap *map;

	int width, height, tileSize;

	int index(int x, int y, int z) {
		return (x * width + y * height + z * width);
	};
	sf::Vector3i XYZ(int index) {
		return sf::Vector3i(index % width, (index / (width*width)) % height, (index / width) % width);
	};


	int NONCOLLISION_TILES[1] = {0};

};

