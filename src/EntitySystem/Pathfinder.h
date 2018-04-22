#pragma once
#include <vector>
#include "../TileSystem/TileMap.h"
class Pathfinder {
public:
	Pathfinder(TileMap * map);
	Pathfinder();

	~Pathfinder();

	void calculateMap(int x, int z);

	void recalculateMap();

	void floodfill(int x, int z, float distance);

	float getHeat(sf::Vector2i pos);

	float getHeat(int x, int z);

	float getHeatDifference(int x, int z);

	float getHeatDifference(sf::Vector2i pos);

	void addHeat(sf::Vector2i pos, double value);

	void printHeat();

	bool canWalkHere(int x, int y);

	void LateUpdate();

	

	sf::Vector2i isoToGrid(sf::Vector3f pos);
	sf::Vector2i isoToGrid(sf::Vector2f pos);

	sf::Vector2f gridToIso(sf::Vector2i pos);
	sf::Vector3f gridToIso(sf::Vector3i pos);

private:

	const int gridPerTile = 1; //squareroot

	int width, height;

	int startX, startY;

	float *distancemap;

	float *lastHeatMap;
	float *heatmap;

	int size;

	TileMap * map;
};

