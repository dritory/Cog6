#include "TileMap.h"
#include <memory>
#include <assert.h>
#include "..\AssetLoader\AssetLoader.h"

bool TileMap::load(const std::string & texturePath, sf::Vector2u _tileTextureSize, sf::Vector2i _tileSize, int _layerDepth, const int _tiles[], unsigned int _width) {

	
	width = _width;
	height = _width;
	tileSize = _tileSize;
	layerDepth = _layerDepth;
	tileTextureSize = _tileTextureSize;
	tiles.reserve(_width*_width);

	for (int i = 0; i < _width*_width; i++) {
		tiles.push_back(_tiles[i]);
	}
	int diagonalRowNum = 2 * _width - 1;
	diagonalRows.reserve(diagonalRowNum);
	for (int i = diagonalRowNum - 1; i >= 0; --i) {

		int tilesBeyondWidth = (i - (int)_width + 1)*(int)(i / _width);
		int coloumnNum = 1 + i - 2 * tilesBeyondWidth;
		int offset = _width * (i - tilesBeyondWidth);

		Row row;
		row.load(texturePath, tileTextureSize, tileSize, i, tiles, offset, coloumnNum, _width);
		sf::Vector2f vector = isoTo2D(sf::Vector2f((-(coloumnNum / 2))*tileSize.x + (i % 2)*tileSize.x / 2, (i)*(tileSize.y / 4)));
		row.SetPosition(sf::Vector3f(vector.x, layerDepth * tileSize.y, vector.y));

		diagonalRows.push_back(row);
	}
	std::reverse(diagonalRows.begin(), diagonalRows.end());
	return true;
}

int TileMap::getTileId(unsigned int x, unsigned int z) {
	return tiles[x + z * width];
}

void TileMap::setTileId(int x, int z, int id) {
	if (x >= 0 && x < width && z >= 0 && z < height) {
		tiles[x + z * (int)width] = id;
		int tilesBeyondWidth = ((x + z) - (int)width + 1)*(int)((x + z) / (int)width);
		diagonalRows[(x + z)].setTileId(x - tilesBeyondWidth, id, tileTextureSize);
	}
}

sf::Vector2i TileMap::getTileSize()  const {
	return tileSize;
}

int TileMap::getDepth() const {
	return layerDepth;
}

bool TileMap::canWalkHere(unsigned int x, unsigned int z, const int nonCollisionTiles[]) {
	int tile = getTileId(x, z);
	for (int i = 0; i < sizeof(nonCollisionTiles) / sizeof(nonCollisionTiles[0]); i++) {
		if (i == tile)
			return true;
	}
	return false;
}
std::vector<TileMap::Row> &TileMap::getRows() {

	return diagonalRows;
}

sf::Vector2f TileMap::isoTo2D(sf::Vector2f point) {
	return  sf::Vector2f((2 * point.y + point.x), (2 * point.y - point.x));
}

sf::Vector2i TileMap::isoToTile(sf::Vector2f point, const TileMap & map) {
	sf::Vector2f twoD = isoTo2D(point);
	return  sf::Vector2i(twoD.x / map.tileSize.x, twoD.y / map.tileSize.y);
}

sf::Vector2i TileMap::screenToTile(sf::Vector2i point, const TileMap & map, const sf::RenderWindow &window) {
	sf::Vector2f twoD = isoTo2D(window.mapPixelToCoords(point));
	return sf::Vector2i(twoD.x / map.tileSize.x, twoD.y / map.tileSize.y);
}

sf::Vector2f TileMap::screenToIso(sf::Vector2i point, const sf::RenderWindow &window) {
	return window.mapPixelToCoords(point);
}

sf::Vector2f TileMap::screenTo2D(sf::Vector2i point, const sf::RenderWindow & window) {
	return isoTo2D(window.mapPixelToCoords(point));
}

sf::Vector2i TileMap::mouseToTile(const TileMap & map, const sf::RenderWindow & window) {
	sf::Vector2f twoD = isoTo2D(window.mapPixelToCoords(sf::Mouse::getPosition(window)) + sf::Vector2f(map.getTileSize().x * -0.5f, map.getTileSize().y *(map.getDepth() - 0.5f) / 2.0f));
	return sf::Vector2i(twoD.x / map.tileSize.x, twoD.y / map.tileSize.y);
}

sf::Vector2f TileMap::twoDToIso(sf::Vector2f point) {
	return sf::Vector2f((point.x + point.y) / 2.0f, point.y - point.x);
}

bool TileMap::Row::load(const std::string & texturePath, sf::Vector2u tileTextureSize, sf::Vector2i tileSize, int rowNumber, const std::vector<int> tiles, int offset, int coloumns, unsigned int width) {

	auto tex = AssetLoader<sf::Texture>::GetInstance().Get(texturePath);
	if (tex == nullptr) {
		bool loaded = AssetLoader<sf::Texture>::GetInstance().LoadAsset(texturePath);
		if (!loaded) return false; 
			tex = AssetLoader<sf::Texture>::GetInstance().Get(texturePath);
	}
	m_tileset = *tex;
	m_vertices.setPrimitiveType(sf::Quads);
	m_vertices.resize(coloumns * 4);

	for (int i = 0; i < coloumns; ++i) {
		// get the current tile number
		const int tileNumber = tiles[offset - (width - 1)*(i)];

		// find its position in the tileset texture
		int tu = tileNumber % (m_tileset.getSize().x / tileTextureSize.x);
		int tv = tileNumber / (m_tileset.getSize().x / tileTextureSize.x);

		// get a pointer to the current tile's quad
		sf::Vertex* quad = &m_vertices[(i) * 4];

		quad[0].position = sf::Vector2f(i * tileSize.x, 0);
		quad[1].position = sf::Vector2f((i * tileSize.x) + tileSize.x, 0);
		quad[2].position = sf::Vector2f((i  * tileSize.x) + tileSize.x, tileSize.y);
		quad[3].position = sf::Vector2f((i * tileSize.x), tileSize.y);

		// define its 4 texture coordinates
		quad[0].texCoords = sf::Vector2f(tu * tileTextureSize.x, tv * tileTextureSize.y);
		quad[1].texCoords = sf::Vector2f((tu + 1) * tileTextureSize.x, tv * tileTextureSize.y);
		quad[2].texCoords = sf::Vector2f((tu + 1) * tileTextureSize.x, (tv + 1) * tileTextureSize.y);
		quad[3].texCoords = sf::Vector2f(tu * tileTextureSize.x, (tv + 1) * tileTextureSize.y);
	}
	return true;
}

void TileMap::Row::draw(sf::RenderTarget & target, sf::RenderStates states) const {
	// apply the transform
	states.transform *= getTransform();

	// apply the tileset texture
	states.texture = &m_tileset;

	// draw the vertex array
	target.draw(m_vertices, states);
}

void TileMap::Row::setTileId(int x, int tileId, sf::Vector2u tileTextureSize) {
	int tu = tileId % (m_tileset.getSize().x / tileTextureSize.x);
	int tv = tileId / (m_tileset.getSize().x / tileTextureSize.x);

	if ((x) * 4 < m_vertices.getVertexCount()) {

		sf::Vertex* quad = &m_vertices[(x) * 4];

		quad[0].texCoords = sf::Vector2f(tu * tileTextureSize.x, tv * tileTextureSize.y);
		quad[1].texCoords = sf::Vector2f((tu + 1) * tileTextureSize.x, tv * tileTextureSize.y);
		quad[2].texCoords = sf::Vector2f((tu + 1) * tileTextureSize.x, (tv + 1) * tileTextureSize.y);
		quad[3].texCoords = sf::Vector2f(tu * tileTextureSize.x, (tv + 1) * tileTextureSize.y);
	}
}
