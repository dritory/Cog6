#pragma once
#include <SFML\Graphics.hpp>
#include <cmath>
class TileMap : public sf::Drawable, public sf::Transformable {
private:
	class Row : public sf::Drawable, public sf::Transformable{
	public:
		bool load(const std::string& tileset,sf::Vector2u tileTextureSize, sf::Vector2u tileSize,int rowNumber, std::vector<int>, unsigned int width);
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		
		sf::VertexArray m_vertices;
		sf::Texture m_tileset;
		double depth = 0.0;
	};


public:
	bool load(const std::string& tileset,sf::Vector2u tileTextureSize, sf::Vector2u tileSize,int layerDepth, const int tiles[], unsigned int width, unsigned int height);

	int getTileId(unsigned int x, unsigned int y);
	void setTileId(unsigned int x, unsigned int y, int id);

	bool canWalkHere(unsigned int x, unsigned int y);
	
	std::vector<TileMap::Row> *getRows();

	static sf::Vector2f pointToIso(sf::Vector2f point);
	static sf::Vector2f isoTo2D(sf::Vector2f point);

private:

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void refreshVertexArray(int tiles[]);
	
	std::vector<TileMap::Row> diagonalRows;

	

	sf::VertexArray m_vertices;
	sf::Texture m_tileset;
	sf::Vector2u tileSize;
	sf::Vector2u tileTextureSize;
	int layerDepth = 0;
	
	unsigned int width;
	unsigned int height;
	
	int *tiles;

	

};
