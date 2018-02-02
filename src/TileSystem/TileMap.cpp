#include "TileMap.h"
#include <memory>
bool TileMap::load(const std::string & tileset, sf::Vector2u tileTextureSize, sf::Vector2u tileSize, int layerDepth, const int tiles[], unsigned int width, unsigned int height) {
	// load the tileset texture
	if (!m_tileset.loadFromFile(tileset))
		return false;

	this->width = width;
	this->height = height;
	this->tileSize = tileSize;
	this->layerDepth = layerDepth;
	this->tileTextureSize = tileTextureSize;


	int diagonalRowNum = width + height - 1;

	for (int i = 0; i < diagonalRowNum; ++i) {

		int tilesBeyondWidth = (i - (int)width + 1)*(int)(i / width);
		int coloumnNum = 1 + i - 2 * tilesBeyondWidth;
		int offset = width*(i - tilesBeyondWidth);
		std::vector<int> rowTiles;
		rowTiles.reserve(coloumnNum*2);

		Row row;

		for (int j = 0; j < coloumnNum; ++j) {

			rowTiles.push_back(tiles[offset - (width - 1)*( j )]);
		}

		row.load(tileset, tileTextureSize, tileSize, i, rowTiles, coloumnNum);
		row.setPosition(sf::Vector2f((-(coloumnNum / 2))*(int)tileSize.x + (i % 2)*(int)tileSize.x/2,i*((int)tileSize.y/4) - layerDepth*(int)tileSize.y/2) + getPosition());

		diagonalRows.push_back(row);
	}





	// resize the vertex array to fit the level size
	m_vertices.setPrimitiveType(sf::Quads);
	m_vertices.resize(width * height * 4);
	// populate the vertex array, with one quad per tile
	for (int i = 0; i < width; ++i)
		for (int j = 0; j < height; ++j) {
			// get the current tile number
			int tileNumber = tiles[i + j * width];

			// find its position in the tileset texture
			int tu = tileNumber % (m_tileset.getSize().x / tileTextureSize.x);
			int tv = tileNumber / (m_tileset.getSize().x / tileTextureSize.x);

			// get a pointer to the current tile's quad
			sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

			// define its 4 corners
			/*
			float offset = (j % 2)*(tileSize.x / 2);
			quad[0].position = sf::Vector2f(i * tileSize.x + offset, j * tileSize.y/2);
			quad[1].position = sf::Vector2f((i + 1) * tileSize.x+ offset, j * tileSize.y/2);
			quad[2].position = sf::Vector2f((i + 1) * tileSize.x + offset, (j * tileSize.y/2) + tileSize.y);
			quad[3].position = sf::Vector2f(i * tileSize.x + offset, (j * tileSize.y/2) + tileSize.y);
			*/

			sf::Vector2f pos = pointToIso(sf::Vector2f(i, j));

			quad[0].position = sf::Vector2f(pos.x * tileSize.x / 2, pos.y * tileSize.y / 2);
			quad[1].position = sf::Vector2f((pos.x * tileSize.x / 2) + tileSize.x, pos.y * tileSize.y / 2);
			quad[2].position = sf::Vector2f((pos.x  * tileSize.x / 2) + tileSize.x, (pos.y * tileSize.y / 2) + tileSize.y);
			quad[3].position = sf::Vector2f((pos.x * tileSize.x / 2), (pos.y * tileSize.y / 2) + tileSize.y);

			// define its 4 texture coordinates
			quad[0].texCoords = sf::Vector2f(tu * tileTextureSize.x, tv * tileTextureSize.y);
			quad[1].texCoords = sf::Vector2f((tu + 1) * tileTextureSize.x, tv * tileTextureSize.y);
			quad[2].texCoords = sf::Vector2f((tu + 1) * tileTextureSize.x, (tv + 1) * tileTextureSize.y);
			quad[3].texCoords = sf::Vector2f(tu * tileTextureSize.x, (tv + 1) * tileTextureSize.y);
		}


	return true;
}

int TileMap::getTileId(unsigned int x, unsigned int y) {
	return tiles[x + y * width];
}

void TileMap::setTileId(unsigned int x, unsigned int y, int id) {
	tiles[x + y * width] = id;

	// find its position in the tileset texture
	int tu = id % (m_tileset.getSize().x / tileTextureSize.x);
	int tv = id / (m_tileset.getSize().x / tileTextureSize.x);

	// get a pointer to the current tile's quad
	sf::Vertex* quad = &m_vertices[(x + y * width) * 4];

	// define its 4 texture coordinates
	quad[0].texCoords = sf::Vector2f(tu * tileTextureSize.x, tv * tileTextureSize.y);
	quad[1].texCoords = sf::Vector2f((tu + 1) * tileTextureSize.x, tv * tileTextureSize.y);
	quad[2].texCoords = sf::Vector2f((tu + 1) * tileTextureSize.x, (tv + 1) * tileTextureSize.y);
	quad[3].texCoords = sf::Vector2f(tu * tileTextureSize.x, (tv + 1) * tileTextureSize.y);

}

bool TileMap::canWalkHere(unsigned int x, unsigned int y) {
	return true;
}
std::vector<TileMap::Row> *TileMap::getRows() {
	return &diagonalRows;
}

sf::Vector2f TileMap::isoTo2D(sf::Vector2f point) {
	return  sf::Vector2f((2 * point.y + point.x) / 2, (2 * point.y - point.x) / 2);
}

void TileMap::draw(sf::RenderTarget & target, sf::RenderStates states) const {
	// apply the transform
	states.transform *= getTransform();

	// apply the tileset texture
	states.texture = &m_tileset;

	// draw the vertex array
	//target.draw(m_vertices, states);

}

void TileMap::refreshVertexArray(int tiles[]) {
	for (int i = 0; i < width; ++i)
		for (int j = 0; j < height; ++j) {
			// get the current tile number
			int tileNumber = tiles[i + j * width];

			// find its position in the tileset texture
			int tu = tileNumber % (m_tileset.getSize().x / tileTextureSize.x);
			int tv = tileNumber / (m_tileset.getSize().x / tileTextureSize.x);

			// get a pointer to the current tile's quad
			sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

			// define its 4 texture coordinates
			quad[0].texCoords = sf::Vector2f(tu * tileTextureSize.x, tv * tileTextureSize.y);
			quad[1].texCoords = sf::Vector2f((tu + 1) * tileTextureSize.x, tv * tileTextureSize.y);
			quad[2].texCoords = sf::Vector2f((tu + 1) * tileTextureSize.x, (tv + 1) * tileTextureSize.y);
			quad[3].texCoords = sf::Vector2f(tu * tileTextureSize.x, (tv + 1) * tileTextureSize.y);
		}
}


sf::Vector2f TileMap::pointToIso(sf::Vector2f point) {
	return sf::Vector2f(point.x - point.y, (point.x + point.y) / 2.0f);
}

bool TileMap::Row::load(const std::string & tileset, sf::Vector2u tileTextureSize, sf::Vector2u tileSize, int rowNumber, std::vector<int> tiles, unsigned int width) {
	if (!m_tileset.loadFromFile(tileset))
		return false;
	
	

	m_vertices.setPrimitiveType(sf::Quads);
	m_vertices.resize(width * 4);

	for (int i = 0; i < width; ++i) {
		// get the current tile number
		int tileNumber = tiles[i];

		// find its position in the tileset texture
		int tu = tileNumber % (m_tileset.getSize().x / tileTextureSize.x);
		int tv = tileNumber / (m_tileset.getSize().x / tileTextureSize.x);

		// get a pointer to the current tile's quad
		sf::Vertex* quad = &m_vertices[(i) * 4];

		// define its 4 corners
		/*
		float offset = (j % 2)*(tileSize.x / 2);
		quad[0].position = sf::Vector2f(i * tileSize.x + offset, j * tileSize.y/2);
		quad[1].position = sf::Vector2f((i + 1) * tileSize.x+ offset, j * tileSize.y/2);
		quad[2].position = sf::Vector2f((i + 1) * tileSize.x + offset, (j * tileSize.y/2) + tileSize.y);
		quad[3].position = sf::Vector2f(i * tileSize.x + offset, (j * tileSize.y/2) + tileSize.y);
		*/

		//sf::Vector2f pos = pointToIso(sf::Vector2f(i, j));

		quad[0].position = sf::Vector2f(i * tileSize.x, 0);
		quad[1].position = sf::Vector2f((i * tileSize.x ) + tileSize.x, 0);
		quad[2].position = sf::Vector2f((i  * tileSize.x ) + tileSize.x, tileSize.y);
		quad[3].position = sf::Vector2f((i * tileSize.x ), tileSize.y);

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
