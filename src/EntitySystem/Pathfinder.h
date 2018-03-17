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

	void addHeat(sf::Vector2i pos, double value);

	void printHeat();

	void LateUpdate();

private:
	int width, height;

	int startX, startY;

	std::vector<float> distancemap;

	std::vector<float> heatmap;

	TileMap * map;
};

