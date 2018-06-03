#include "TileMap.h"
#include <memory>
#include <assert.h>
#include "..\AssetLoader\AssetLoader.h"
#include "..\Game.h"
#include "TileSystem.h"

TileMap::TileMap()
{
	collisionMap = nullptr;
}

TileMap::~TileMap()
{
	delete[] collisionMap;
	collisionMap = nullptr;

}
bool TileMap::load(const std::string & texturePath, sf::Vector2u _tileTextureSize, sf::Vector2i _tileSize, int _layerDepth, const int _tiles[], unsigned int _width, const int nonCollisionTiles[]) {
	width = _width;
	height = _width;
	tileSize = _tileSize;
	layerDepth = _layerDepth;
	tileTextureSize = _tileTextureSize;

	tiles.resize(_width*_width);
	collisionMap = new bool[_width*_width];

	for (int i = 0; i < (int)(_width*_width); i++) {
		tiles[i] = _tiles[i];
		bool noncollision = false;
		for (int j = 0; j < sizeof(nonCollisionTiles) / sizeof(nonCollisionTiles[0]); j++) {
			if (nonCollisionTiles[j] == _tiles[i]) {
				noncollision = true;
			}
		}
		collisionMap[i] = !noncollision;
	}
	int diagonalRowNum = 2 * _width - 1;
	diagonalRows.resize(diagonalRowNum);
	for (int i = 0; i <  diagonalRowNum; ++i) {

		int tilesBeyondWidth = (i - (int)_width + 1)*(int)(i / _width);
		int coloumnNum = 1 + i - 2 * tilesBeyondWidth;
		int offset = _width * ( i  -tilesBeyondWidth ) + tilesBeyondWidth;

 		Row row;
		row.load(texturePath, tileTextureSize, tileSize, i, tiles, offset, coloumnNum, _width);
		sf::Vector2f vector = worldToIso(sf::Vector2f((float)(-(coloumnNum / 2))*tileSize.x + (i % 2)*tileSize.x / 2, (float)(i)*(tileSize.y / 4)));
		row.SetPosition(sf::Vector3f((float)vector.x, (float)layerDepth * tileSize.y, (float)vector.y));

		diagonalRows[i] = std::move(row);
		
	}
	//std::reverse(diagonalRows.begin(), diagonalRows.end());
	return true;
}

int TileMap::getTileId(unsigned int x, unsigned int z) {
	if (x >= 0 && x < width && z >= 0 && z < height) {
		return tiles[x + z * width];
	}
	return 0;
}

void TileMap::setTileId(int x, int z, int id, const int nonCollisionTiles []) {
	if (x >= 0 && x < (int)width && z >= 0 && z < (int)height) {
		tiles[x + z * (int)width] = id;
		
		bool nonCollision = false;
		for (int i = 0; i < sizeof(nonCollisionTiles) / sizeof(nonCollisionTiles[0]); i++) {
			if (nonCollisionTiles[i] == id) {
				nonCollision = true;
			}
		}

		if (collisionMap[x + z * (int)width] != !nonCollision) {
			collisionMap[x + z * (int)width] = !nonCollision;
			Game::instance().getTileSystem().pathfinder->recalculateMap();
		}
		
		int tilesBeyondWidth = ((x + z) - (int)width + 1)*(int)((x + z) / (int)width);
		diagonalRows[(x + z)].setTileId(x - tilesBeyondWidth, id, tileTextureSize);
	}
}

const sf::Vector2i &TileMap::getTileSize()  const {
	return tileSize;
}

int TileMap::getDepth() const {
	return layerDepth;
}

int TileMap::getWidth() const{
	return width;
}

int TileMap::getHeight() const{
	return height;
}

bool TileMap::canWalkHere(unsigned int x, unsigned int z) {
	if (x >= 0 && x < width && z >= 0 && z < height)
		return (!collisionMap[x + z * width]);
	else
		return false;
}
void TileMap::setCollision(int x, int z, bool collidable)
{
	if (x >= 0 && x < (int)width && z >= 0 && z < (int)height)
		collisionMap[x + z *width] = collidable;
}
std::vector<TileMap::Row> &TileMap::getRows() {

	return diagonalRows;
}

const bool *TileMap::getCollisionMap() {
	return collisionMap;
}

sf::Vector2f TileMap::worldToIso(sf::Vector2f point) {
	return  sf::Vector2f((2 * point.y + point.x), (2 * point.y - point.x));
}

sf::Vector2i TileMap::worldToTile(sf::Vector2f point) {
	sf::Vector2f twoD = worldToIso(point);
	sf::Vector2i tile = sf::Vector2i((int)(twoD.x / tileSize.x), (int)(twoD.y / tileSize.y));
	return  tile;
}

sf::Vector2f TileMap::tileToWorld(sf::Vector2i point) {
	return isoToWorld(sf::Vector2f((float)(point.x * tileSize.x),(float)(point.y * tileSize.y)));
}

sf::Vector2i TileMap::screenToTile(sf::Vector2i point, const sf::RenderWindow &window) {
	sf::Vector2f twoD = worldToIso(window.mapPixelToCoords(point));
	return sf::Vector2i((int)(twoD.x / tileSize.x), (int)(twoD.y / tileSize.y));
}

sf::Vector2f TileMap::screenToWorld(sf::Vector2i point, const sf::RenderWindow &window) {
	return window.mapPixelToCoords(point);
}

sf::Vector2f TileMap::screenToIso(sf::Vector2i point, const sf::RenderWindow & window) {
	return worldToIso(window.mapPixelToCoords(point));
}

sf::Vector2i TileMap::mouseToTile(const sf::RenderWindow & window) {
	sf::Vector2f offset(this->tileSize.x * -0.5f, this->tileSize.y *(this->layerDepth - 0.5f) / 2.0f);
	sf::Vector2f twoD = worldToIso(window.mapPixelToCoords(sf::Mouse::getPosition(window)) + offset);
	return sf::Vector2i((int)(twoD.x / tileSize.x), (int)(twoD.y / this->tileSize.y));
}

sf::Vector2f TileMap::isoToWorld(sf::Vector2f point) {
	return sf::Vector2f((point.x - point.y) / 2.0f, (point.y + point.x) / 4.0f);
}

bool TileMap::Row::load(const std::string & texturePath, sf::Vector2u tileTextureSize, sf::Vector2i tileSize, int rowNumber, const std::vector<int>& tiles, int offset, int coloumns, unsigned int width) {
	auto tex = AssetLoader<sf::Texture>::GetInstance().Get(texturePath);
	if (tex == nullptr) {
		bool loaded = AssetLoader<sf::Texture>::GetInstance().LoadAsset(texturePath);
		if (!loaded) return false; 
			tex = AssetLoader<sf::Texture>::GetInstance().Get(texturePath);
	}
	m_tileset = tex;
	m_vertices.setPrimitiveType(sf::Quads);
	m_vertices.resize(coloumns * 4);

	for (int i = 0; i < coloumns; ++i) {
		// get the current tile number
		int index = offset - ((int)width - 1)*(i);
		const int tileNumber = tiles[index];

		// find its position in the tileset texture
		int tu = tileNumber % (m_tileset->getSize().x / tileTextureSize.x);
		int tv = tileNumber / (m_tileset->getSize().x / tileTextureSize.x);

		// get a pointer to the current tile's quad
		sf::Vertex* quad = &m_vertices[(i) * 4];

		quad[0].position = sf::Vector2f((float)i * tileSize.x, 0);
		quad[1].position = sf::Vector2f((float)(i * tileSize.x) + tileSize.x, 0);
		quad[2].position = sf::Vector2f((float)(i  * tileSize.x) + tileSize.x, (float)tileSize.y);
		quad[3].position = sf::Vector2f((float)(i * tileSize.x), (float)tileSize.y);

		// define its 4 texture coordinates
		quad[0].texCoords = sf::Vector2f((float)tu * tileTextureSize.x, (float)tv * tileTextureSize.y);
		quad[1].texCoords = sf::Vector2f((float)(tu + 1) * tileTextureSize.x, (float)tv * tileTextureSize.y);
		quad[2].texCoords = sf::Vector2f((float)(tu + 1) * tileTextureSize.x, (float)(tv + 1) * tileTextureSize.y);
		quad[3].texCoords = sf::Vector2f((float)tu * tileTextureSize.x, (float)(tv + 1) * tileTextureSize.y);

		
		
	}
	return true;
}

void TileMap::Row::draw(sf::RenderTarget & target, sf::RenderStates states) const {
	// apply the transform
	states.transform *= getTransform();

	// apply the tileset texture
	states.texture = m_tileset;

	// draw the vertex array
	target.draw(m_vertices, states);
}

void TileMap::Row::setTileId(int x, int tileId, sf::Vector2u tileTextureSize) {
	if (m_tileset != nullptr) {
		int tu = tileId % (m_tileset->getSize().x / tileTextureSize.x);
		int tv = tileId / (m_tileset->getSize().x / tileTextureSize.x);

		if ((x) * 4 < m_vertices.getVertexCount()) {

			sf::Vertex* quad = &m_vertices[(x) * 4];

			quad[0].texCoords = sf::Vector2f((float)tu * tileTextureSize.x, (float)tv * tileTextureSize.y);
			quad[1].texCoords = sf::Vector2f((float)(tu + 1) * tileTextureSize.x, (float)tv * tileTextureSize.y);
			quad[2].texCoords = sf::Vector2f((float)(tu + 1) * tileTextureSize.x, (float)(tv + 1) * tileTextureSize.y);
			quad[3].texCoords = sf::Vector2f((float)tu * tileTextureSize.x, (float)(tv + 1) * tileTextureSize.y);
		}
	}
}
