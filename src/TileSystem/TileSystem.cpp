#include "TileSystem.h"

#include "..\Game.h"
#include <random>
#include <ctime>
TileSystem::TileSystem(int width, int height, int tileSize) : width(width),height(height) , tileSize(tileSize) {
	
	map = new TileMap[height];

	pathfinder = nullptr;
	
	tileEntities = new TileEntity * [width*height*width];
	for (int i = 0; i < width*height*width; i++) {
		tileEntities[i] = nullptr;
	}

}


TileSystem::~TileSystem() {
	delete pathfinder;
	pathfinder = nullptr;

	for (int i = 0; i < width*height*width; i++) {
		tileEntities[i] = nullptr;
	}

	delete[] tileEntities;
	tileEntities = nullptr;

	delete[] map;
	map = nullptr;

}

void TileSystem::load() {
	int *level = new int[width*width];
	int *level2 = new int[width*width];
	int *level3 = new int[width*width];
	Game::instance().getNoiseGen().SetFrequency(0.02);
	for (int i = 0; i < width*width; i++) {
		level[i] = 5;
		int x = i % width;
		int y = i / width;
		float f = Game::instance().getNoiseGen().GetSimplexFractal((2 * y + x), (2 * y - x));
		level2[i] = f < -0.2f ? 5 : 0;
		level3[i] = f < -0.5f ? 5 : 0;
	}
		
	// create the tilemap from the level definition

	map[0].load("textures/tileset.png", sf::Vector2u(32, 32), sf::Vector2i(tileSize, tileSize), 0, level, width, NONCOLLISION_TILES);
	map[1].load("textures/tileset.png", sf::Vector2u(32, 32), sf::Vector2i(tileSize, tileSize), 1, level2, width, NONCOLLISION_TILES);
	map[2].load("textures/tileset.png", sf::Vector2u(32, 32), sf::Vector2i(tileSize, tileSize), 2, level3, width, NONCOLLISION_TILES);
	if(pathfinder != nullptr)
		delete pathfinder;

	pathfinder = new Pathfinder(&map[1]);
	delete[] level;
	delete[] level2;
	
	delete[] level3;
	level = nullptr;
	level3 = nullptr;
	level2 = nullptr;
}

void TileSystem::LateUpdate()
{
	pathfinder->LateUpdate();
}

void TileSystem::draw(SpriteBatch &batch) {
	
	static bool oldMouseState = false;

	for (int i = 0; i < height; i ++) {
		
		for (GameObject &d : map[i].getRows()) {
			batch.QueueObject(&d);
		}

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Y)) {
		sf::Vector2i tile = map[1].mouseToTile(Game::instance().getWindow());
		//setTileId(tile.x, 1,tile.y,5);
		pathfinder->calculateMap(tile.x, tile.y);
				//map[0].sprite.setPosition(map[0].getPosition());
	}
	
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && !oldMouseState) {
		sf::Vector2i tile = map[1].mouseToTile(Game::instance().getWindow());
		int tileId = getTileId(tile.x, 1, tile.y);
		setTileId(tile.x, 1,tile.y,(tileId  == 5 ? 0 : 5));
		if (getTileEntity(tile.x, 1, tile.y) != nullptr) {
			Game::instance().getEntitySystem().RemoveEntity(getTileEntity(tile.x, 1, tile.y));
		}
	}
	oldMouseState = sf::Mouse::isButtonPressed(sf::Mouse::Right);
}

//brief checks if the position is walkable
//takes in world coords (iso)
//return true if walkable and false if not
bool TileSystem::canWalkHere(int x, int y, int z) {
	int tm = y;
	if (tm < height && tm > 0) {
		return map[tm].canWalkHere(x, z);
	}
	return true;
}
bool TileSystem::canWalkHere(sf::Vector3i pos)
{
	return canWalkHere(pos.x, pos.y, pos.z);
}
void TileSystem::setCollision(int x, int y, int z, bool collidable)
{
	if (y < height && y >= 0) {
		map[y].setCollision(x, z, collidable);
	}
}
bool TileSystem::isInBounds(int x, int y, int z)
{
	if (x >= 0 && x < width)
		if (z >= 0 && z < width)
			if (y >= 0 && y < height) {
				return true;
			}
	return false;
}
bool TileSystem::isInBounds(sf::Vector3i pos)
{
	return isInBounds(pos.x, pos.y, pos.z);
}
//brief gets the tile id
//takes in tile coords
//return int tile id
int TileSystem::getTileId(int x, int y, int z)
{
	
	if (y < height && y >= 0) {

		return map[y].getTileId(x, z);
	}
	return 0;
}

//brief gets the tile id
//takes in iso coords
//return int tile id
int TileSystem::getTileId(sf::Vector3i pos)
{
	int tm = pos.y / width;
	if (tm < height && tm >= 0) {

		return map[tm].getTileId(pos.x /tileSize, pos.z /tileSize);
	}
	return 0;
}
//brief sets the tile id
//takes in world coords and tile id
void TileSystem::setTileId(sf::Vector3f pos, int id)
{
	int tm = pos.y / width;
	if (tm < height && tm >= 0) {
		
		map[tm].setTileId(pos.x / tileSize, pos.z / tileSize, id, NONCOLLISION_TILES);
	}
}
//brief sets the tile id
//takes in tile coords and tile id
void TileSystem::setTileId(int x, int y, int z, int id)
{
	int tm = y;
	if (tm < height && tm >= 0) {
		map[tm].setTileId(x, z, id, NONCOLLISION_TILES);
	}
}
void TileSystem::setTileEntity(int x, int y, int z, TileEntity *entity)
{
	if (isInBounds(x, y, z)) {
		tileEntities[x + y * height*width + z * width] = entity;
	}
}
TileEntity * TileSystem::getTileEntity(int x, int y, int z)
{
	if (isInBounds(x, y, z))
		return tileEntities[x + y * height*width + z * width];
	else
		return nullptr;
}
sf::Vector2i TileSystem::worldToTileCoord(sf::Vector3f pos) {
	return getMap(pos.y).worldToTile(sf::Vector2f(pos.x, pos.z));
}
sf::Vector2i TileSystem::isoToTileCoord(sf::Vector3f pos)
{
	
	return sf::Vector2i(pos.x / tileSize,pos.z /tileSize);
}
sf::Vector3f TileSystem::tileToIsoCoord(sf::Vector3i pos)
{
	return sf::Vector3f(pos.x * tileSize, pos.y * tileSize, pos.z * tileSize);
}
//brief gets a reference to a map
//takes in world coord y
TileMap & TileSystem::getMap(unsigned int y)
{
	int tm = y / width;
	if (tm < height && tm >= 0) {
		return map[tm];
	}
	
}

