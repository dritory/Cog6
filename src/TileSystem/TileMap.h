#pragma once
#include <SFML\Graphics.hpp>
#include <cmath>
#include "../GameObject.h"

class TileMap : public sf::Transformable {
private:
	class Row : public GameObject {
	public:
		bool load(const std::string& tileset,sf::Vector2u tileTextureSize, sf::Vector2i tileSize,int rowNumber, const std::vector<int>& tiles, int offset,int coloumns, unsigned int width);
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		void setTileId(int x, int tileId, sf::Vector2u tileTextureSize);
		void setColor(int x, sf::Color color);
		bool last = false;

		int layer = 0;
		bool isEmpty() {
			return empty;
		}

	private:
		sf::VertexArray m_vertices;
		sf::Texture* m_tileset;
		bool empty = true;
		
	};

public:
	TileMap();
	~TileMap();
	//loads the map and generates rows
	//takes in tileset as a filename
	bool load(const std::string& texturePath,sf::Vector2u tileTextureSize, sf::Vector2i tileSize,int layerDepth, const int tiles[], unsigned int width, const int collisionIDs[]);

	int getTileId(unsigned int x, unsigned int z);
	void setTileId(int x, int z, int id, const int nonCollisionTiles []);

	void colorTile (unsigned int x, unsigned int z, sf::Color color);

	const sf::Vector2i &getTileSize() const;
	int getDepth() const ;

	int getWidth() const;
	int getHeight() const;

	//brief checks if the tile is walkable
	//Takes in a x and y and tiles that are walkable and returns true if it is walkable
	bool canWalkHere(unsigned int x, unsigned int z);

	void setCollision(int x, int z, bool collidable);

	std::vector<TileMap::Row> &getRows();

	const bool *getCollisionMap();

	//brief converts iso coords to world coords
	//return float vector with worlds coords
	static sf::Vector2f isoToWorld(sf::Vector2f point);

	//brief converts world coords to iso coords
	//return float vector with iso coords
	static sf::Vector2f worldToIso(sf::Vector2f point);

	static sf::Vector2i isoToScreen(sf::Vector2f point, const sf::RenderWindow &window);

	//brief converts world coords to a tile coord in the map
	//return int vector with tile coords
	sf::Vector2i worldToTile(sf::Vector2f point);

	sf::Vector2f tileToWorld(sf::Vector2i point);

	//brief converts pixel coords from the window to tile coords on the map
	//return integer vector with x and y tile coords
	sf::Vector2i screenToTile(sf::Vector2i point, const sf::RenderWindow &window);

	//brief: converts pixel coords from the window to world coords (quite useless)
	//return: float vector with x and y world coords
	static sf::Vector2f screenToWorld(sf::Vector2i point, const sf::RenderWindow &window);

	//brief: converts pixel coords from the window to iso coords on the map
	//return: float vector with x and y iso coords
	static sf::Vector2f screenToIso(sf::Vector2i point, const sf::RenderWindow &window);
	//brief: outputs tile coords from the position of the mouse
	//return: integer vector with x and y tile coords
	sf::Vector2i mouseToTile(const sf::RenderWindow &window);

private:

	std::vector<TileMap::Row> diagonalRows;
	sf::VertexArray m_vertices;
	sf::Texture* m_tileset;
	sf::Vector2i tileSize;
	sf::Vector2u tileTextureSize;
	int layerDepth = 0;
	
	unsigned int width;
	unsigned int height;
	std::vector<int>tiles;
	bool *collisionMap;
	

};
