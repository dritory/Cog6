#include "Pathfinder.h"
#include <utility>
#include <iostream>
#include <queue>
#include "../PlayState.h"
Pathfinder::Pathfinder(TileMap * map) : startX(-1), startY(-1) {
	gridPerTile = 1;
	this->map = map;
	this->width = map->getWidth() * gridPerTile;
	this->height = map->getHeight() * gridPerTile;
	this->size = width * height;
	heatmap = new float[size];
	distancemap = new float[size];
	lastHeatMap = new float[size];
	for ( int i = 0; i < map->getWidth()*map->getHeight() *gridPerTile* gridPerTile; i++ ) {
		heatmap[i] = FLT_MAX;
		distancemap[i] = FLT_MAX;
		lastHeatMap[i] = FLT_MAX;
	}
}
Pathfinder::Pathfinder() {
	gridPerTile = 2;
	heatmap = nullptr;
	distancemap = nullptr;
}
Pathfinder::~Pathfinder() {
	delete[] heatmap;
	delete[] distancemap;

	heatmap = nullptr;
	distancemap = nullptr;
}
//takes in tile coords
void Pathfinder::calculateMap(int x, int y) {
	startX = x;
	startY = y;
	targets.insert(std::make_pair(x, y));
	recalculateMap();
}

void Pathfinder::recalculateMap() {
	maxHeat = 0;
	int width = map->getWidth()* gridPerTile;
	int height = map->getHeight() * gridPerTile;
	for ( int i = 0; i < width*height; i++ ) {
		distancemap[i] = FLT_MAX;
		lastHeatMap[i] = FLT_MAX;
	}
	for ( auto p : targets ) {
		floodfill(p.first * gridPerTile, p.second * gridPerTile, 0);
	}
	//heatmap = distancemap;
	/*
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {

			int i = x + y * height;
			if (distancemap[i] == FLT_MAX) {
				for (int j = -1; j <= 1; j++) {
					for (int k = -1; k <= 1; k++) {
						if (distancemap[x + j + ((y + k) * height)] < FLT_MAX) {

							distancemap[x + j + ((y + k) * height)] += 0.1f;
						}
					}
				}
			}
			heatmap[i] = distancemap[i];
		}
	}

	*/
	//printHeat();
	for ( int i = 0; i < width*height; i++ ) {

		if ( distancemap[i] > maxHeat &&  distancemap[i] != FLT_MAX) {
			maxHeat = distancemap[i];
		}
		if ( heatmap[i] < minHeat ) {
			minHeat = heatmap[i];
		}
		lastHeatMap[i] = distancemap[i];
	}
}

void Pathfinder::floodfill(int x, int z, float distance) {
	if ( x >= 0 && x < width && z >= 0 && z < height ) {
		std::queue<std::pair<int, int> > q;
		q.push(std::make_pair(x, z));
		distancemap[x + z * width] = distance;

		TileSystem * system = Game::Instance()->tileSystem;
		int depth = map->getDepth();
		while ( !q.empty() ) {
			std::pair<int, int> curPoint = q.front();
			q.pop();
			float curDistance = distancemap[curPoint.first + curPoint.second * width];
			for ( int i = -1; i <= 1; i++ )
				for ( int j = -1; j <= 1; j++ ) {
					if ( (i + j) % 2 == 0 ) continue;


					std::pair<int, int> nextPoint(curPoint.first + i, curPoint.second + j);
					if ( nextPoint.first >= 0 && nextPoint.first < width
						&& nextPoint.second >= 0 && nextPoint.second < height
						&& distancemap[nextPoint.first + nextPoint.second * width] > curDistance + 1 ) {
						if ( canWalkHere(nextPoint.first, nextPoint.second) ) {
							//float delta = std::max(abs((i + j) / 2.0f), abs((float)j - (float)i));
							//float delta = static_cast<float>(sqrt(i*i + j*j));
							/*
							if (i != 0 && j != 0) { //diagonals
								if (!canWalkHere(nextPoint.first - i, nextPoint.second) && !canWalkHere(nextPoint.first , nextPoint.second - j)) {
									continue;
								}else if(system->getTileEntity(nextPoint.first- i, depth, nextPoint.second) != nullptr && system->getTileEntity(nextPoint.first, depth, nextPoint.second - j) != nullptr)
								{
									continue;
								}
							}
							*/
							float delta = 1.0f;
							TileEntity *e = system->getTileEntity(nextPoint.first, depth, nextPoint.second);
							if ( e != nullptr ) {
								float h = e->getHeat();
								if ( h > 0 ) {
									bool foo = false;
								}
								if ( h > -1.0f )
									delta += h;
							}

							distancemap[nextPoint.first + nextPoint.second * width] = curDistance + delta;

							q.push(nextPoint);

						}
						else {
						}
					}
				}
		}
	}
}

//grid coords
void Pathfinder::addHeat(sf::Vector2i pos, float value) {
	if ( pos.x >= 0 && pos.x < width && pos.y >= 0 && pos.y < height ) {
		heatmap[pos.x + pos.y*width] += value;
		lastHeatMap[pos.x + pos.y*width] += value;
	}
}

float Pathfinder::getHeat(sf::Vector2i pos) {
	return getHeat(pos.x, pos.y);
}

float Pathfinder::getHeat(int x, int z) {
	if ( x >= 0 && x < width && z >= 0 && z < height ) {
		if ( x == startX * gridPerTile && z == startY * gridPerTile ) {
			return 0;
		}
		else {
			return lastHeatMap[x + z * width];
		}
	}
	else
		return FLT_MAX;
}

float Pathfinder::getHeatDifference(sf::Vector2i pos) {
	return getHeatDifference(pos.x, pos.y);
}
float Pathfinder::getMax()
{
	return maxHeat;
}

float Pathfinder::getMin() {
	return minHeat;
}
bool Pathfinder::targetExistsAt(int x, int y) {
	if ( targets.find(std::make_pair(x, y)) != targets.end() ) {
		return true;
	}
	return false;
}
bool Pathfinder::removeTarget(int x, int y) {
	return (targets.erase(std::make_pair(x, y)) > 0);
}
bool Pathfinder::isValid() {
	return (bool) targets.size();
}
bool Pathfinder::isValidAt(float x, float y)
{
	return getHeat(isoToGrid(sf::Vector2f(x, y))) != FLT_MAX;
}
void Pathfinder::flush() {
	for ( int i = 0; i < width*height; i++ ) {
		distancemap[i] = FLT_MAX;
		lastHeatMap[i] = FLT_MAX;
	}
	maxHeat = 0;
	targets.clear();
}
bool Pathfinder::addTarget(int x, int y) {

	return targets.insert(std::make_pair(x, y)).second;
}
float Pathfinder::getHeatDifference(int x, int z) {
	if ( x >= 0 && x < width && z >= 0 && z < height )
		return lastHeatMap[x + z * width] - distancemap[x + z * width];
	else
		return 0;
}

void Pathfinder::printHeat() {
	for ( int i = 0; i < size; i++ ) {
		if ( i % width == 0 ) {
			std::cout << std::endl;
		}
		float h = getHeat(i % width, i / height);
		if ( h >= FLT_MAX - 10 ) {
			std::cout << " X  ";
			continue;
		}
		std::cout << h << (h < 9 ? (h >= 0 ? "   " : "  ") : (h <= 99 ? "  " : " "));

	}
}

bool Pathfinder::canWalkHere(int x, int z) {
	if ( x >= 0 && x < width && z >= 0 && z < height ) {
		return map->canWalkHere(x / gridPerTile, z / gridPerTile);
	}
	return false;
}

void Pathfinder::LateUpdate() {
	for ( int i = 0; i < map->getWidth()*map->getHeight() * gridPerTile* gridPerTile; i++ ) {
		lastHeatMap[i] = heatmap[i];
		if ( heatmap[i] > maxHeat &&  heatmap[i] != FLT_MAX ) {
			maxHeat = heatmap[i];
		}
		if ( heatmap[i] < minHeat ) {
			minHeat = heatmap[i];
		}

		if ( distancemap[i] != FLT_MAX )
			heatmap[i] = distancemap[i];
		else
			heatmap[i] = FLT_MAX;
	}
}

sf::Vector2i Pathfinder::isoToGrid(sf::Vector3f pos) {
	return isoToGrid(sf::Vector2f(pos.x, pos.z));
}

sf::Vector2i Pathfinder::isoToGrid(sf::Vector2f pos) {
	int tileSize = Game::Instance()->tileSystem->getTileSize();
	return sf::Vector2i((int) pos.x / (tileSize / gridPerTile), (int) pos.y / (tileSize / gridPerTile));
}

sf::Vector2f Pathfinder::gridToIso(sf::Vector2i pos) {
	int tileSize = Game::Instance()->tileSystem->getTileSize();
	return sf::Vector2f(pos.x *  (float) (tileSize / gridPerTile), pos.y * (float) (tileSize / gridPerTile));
}

sf::Vector3f Pathfinder::gridToIso(sf::Vector3i pos) {
	int tileSize = Game::Instance()->tileSystem->getTileSize();
	return sf::Vector3f(pos.x *  (float) (tileSize / gridPerTile), pos.y * (float) (tileSize / gridPerTile), pos.z * (float) (tileSize / gridPerTile));
}
