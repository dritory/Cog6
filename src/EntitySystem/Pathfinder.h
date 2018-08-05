#pragma once
#include <vector>
#include "../TileSystem/TileMap.h"
#include <set>
#include <utility>
class Pathfinder {
public:
	Pathfinder(TileMap * map);
	Pathfinder();

	~Pathfinder();

	//adds a target and calls recalculateMap()
	void calculateMap(int x, int z);

	//calculates the heatmap based on the targets
	void recalculateMap();

	float getHeat(sf::Vector2i pos);

	float getHeat(int x, int z);

	float getHeatDifference(int x, int z);

	float getHeatDifference(sf::Vector2i pos);

	float getMax();

	float getMin();

	bool targetExistsAt(int x, int y);

	bool removeTarget(int x, int y);

	bool isValid();
	//iso coords
	bool isValidAt(float x, float y);
	
	//resets the heatmaps and clears all targets
	void flush();

	bool addTarget(int x, int y);

	//adds temperary heat to a point
	void addHeat(sf::Vector2i pos, float value);

	void printHeat();

	bool canWalkHere(int x, int y);

	void LateUpdate();

	
	std::set<std::pair<int,int>> targets;

	sf::Vector2i isoToGrid(sf::Vector3f pos);
	sf::Vector2i isoToGrid(sf::Vector2f pos);

	sf::Vector2f gridToIso(sf::Vector2i pos);
	sf::Vector3f gridToIso(sf::Vector3i pos);

private:

	
	void floodfill(int x, int z, float distance);

	int gridPerTile; //squareroot

	int width, height;

	int startX, startY;

	float *distancemap;

	float *lastHeatMap;
	float *heatmap;

	int size;

	float maxHeat;
	float minHeat;
	TileMap * map;
};

