#include "TileSystem.h"

#include "..\Game.h"
#include <random>
#include <ctime>
TileSystem::TileSystem() {
	srand((unsigned int)time(nullptr));
	
	int *level = new int[WIDTH*WIDTH];
	int *level2 = new int[WIDTH*WIDTH];
	for (int i = 0; i < WIDTH*WIDTH; i++) {
		level[i] = 5;
		level2[i] = (int)(rand() % 100 < 80 ? 0 : 5);
	}
		
	// create the tilemap from the level definition

	map[0].load("textures/tileset.png", sf::Vector2u(32, 32), sf::Vector2i(32, 32), 0, level, WIDTH, NONCOLLISION_TILES);
	map[1].load("textures/tileset.png", sf::Vector2u(32, 32), sf::Vector2i(32, 32), 1, level2, WIDTH, NONCOLLISION_TILES);

	pathfinder = Pathfinder(&map[1]);
	delete[] level;
	delete[] level2;
	level = nullptr;
	level2 = nullptr;
}


TileSystem::~TileSystem() {
}

void TileSystem::load() {
}

void TileSystem::LateUpdate()
{
	pathfinder.LateUpdate();
}

void TileSystem::draw(SpriteBatch &batch) {
	
	static bool oldMouseState = false;

	for (TileMap &m : map) {
		
		for (GameObject &d : m.getRows()) {
			batch.QueueObject(&d);
		}

	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		sf::Vector2i tile = map[1].mouseToTile(Game::instance().getWindow());
		//setTileId(tile.x, 1,tile.y,5);
		pathfinder.calculateMap(tile.x, tile.y);
				//map[0].sprite.setPosition(map[0].getPosition());
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && !oldMouseState) {
		sf::Vector2i tile = map[1].mouseToTile(Game::instance().getWindow());
		int tileId = getTileId(tile.x, 1, tile.y);
		setTileId(tile.x, 1,tile.y,(tileId  == 5 ? 0 : 5));

	}
	oldMouseState = sf::Mouse::isButtonPressed(sf::Mouse::Right);
}

//brief checks if the position is walkable
//takes in world coords (iso)
//return true if walkable and false if not
bool TileSystem::canWalkHere(int x, int y, int z) {
	int tm = y / WIDTH;
	if (tm < HEIGHT && tm > 0) {
		sf::Vector2i size = map[tm].getTileSize();
		return map[tm].canWalkHere(x / size.x, z / size.y);
	}
	return true;
}
bool TileSystem::canWalkHere(sf::Vector3i pos)
{
	return canWalkHere(pos.x, pos.y, pos.z);
}
//brief gets the tile id
//takes in tile coords
//return int tile id
int TileSystem::getTileId(int x, int y, int z)
{
	
	if (y < HEIGHT && y >= 0) {

		sf::Vector2i size = map[y].getTileSize();
		return map[y].getTileId(x, z);
	}
	return 0;
}

//brief gets the tile id
//takes in iso coords
//return int tile id
int TileSystem::getTileId(sf::Vector3i pos)
{
	int tm = pos.y / WIDTH;
	if (tm < HEIGHT && tm >= 0) {

		sf::Vector2i size = map[tm].getTileSize();
		return map[tm].getTileId(pos.x / size.x, pos.z / size.y);
	}
	return 0;
}
//brief sets the tile id
//takes in world coords and tile id
void TileSystem::setTileId(sf::Vector3f pos, int id)
{
	int tm = (int)(pos.y / WIDTH);
	if (tm < HEIGHT && tm >= 0) {
		sf::Vector2i size = map[tm].getTileSize();
		map[tm].setTileId((int)(pos.x / size.x), (int)(pos.z / size.y), id, NONCOLLISION_TILES);
	}
}
//brief sets the tile id
//takes in tile coords and tile id
void TileSystem::setTileId(int x, int y, int z, int id)
{
	int tm = y;
	if (tm < HEIGHT && tm >= 0) {
		map[tm].setTileId(x, z, id, NONCOLLISION_TILES);
	}
}
sf::Vector2i TileSystem::worldToTileCoord(sf::Vector3f pos) {
	return getMap((unsigned int)pos.y).worldToTile(sf::Vector2f(pos.x, pos.z));
}
sf::Vector2i TileSystem::isoToTileCoord(sf::Vector3f pos)
{
	sf::Vector2i tilesize = getMap((unsigned int)pos.y).getTileSize();
	return sf::Vector2i((int)(pos.x / tilesize.x),(int)(pos.z /tilesize.y));
}
sf::Vector3f TileSystem::tileToIsoCoord(sf::Vector3i pos)
{
	sf::Vector2i tilesize = getMap(pos.y).getTileSize();
	return sf::Vector3f((float)pos.x * tilesize.x, (float)pos.y * tilesize.x, (float)pos.z * tilesize.y);
}
//brief gets a reference to a map
//takes in world coord y
TileMap& TileSystem::getMap(unsigned int y)
{
	int tm = y / WIDTH;
	if (tm < HEIGHT && tm >= 0) {
		return map[tm];
	}
	// TODO: Handle better
	throw new std::exception("Map does not exist");
}

