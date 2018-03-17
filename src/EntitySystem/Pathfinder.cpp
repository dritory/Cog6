#include "Pathfinder.h"
#include <utility>
#include <iostream>
#include <queue>
#include "../Game.h"
Pathfinder::Pathfinder(TileMap * map) {

	this->map = map;
	this->width = map->getWidth();
	this->height = map->getHeight();
	for (int i = 0; i < map->getWidth()*map->getHeight(); i++) {
		heatmap.push_back( FLT_MAX);
		distancemap.push_back(FLT_MAX);
	}
	calculateMap(31, 10);
}
Pathfinder::Pathfinder() {
}
Pathfinder::~Pathfinder() {
}

void Pathfinder::calculateMap(int x, int y) {
	startX = x;
	startY = y;
	for (int i = 0; i < map->getWidth()*map->getHeight(); i++) {
		distancemap[i] = FLT_MAX;
	}
	floodfill(x, y, 0);
	heatmap = distancemap;
	//printHeat();
}

void Pathfinder::recalculateMap() {
	calculateMap(startX, startY);
}

void Pathfinder::floodfill(int x, int z, float distance) {
	if (x >= 0 && x < width && z >= 0 && z < height) {
		std::queue<std::pair<int, int> > q;

		q.push(std::make_pair(x, z));
		distancemap[x + z * width] = distance;

		while (!q.empty())
		{
			std::pair<int, int> curPoint = q.front();
			q.pop();
			int curDistance = distancemap[curPoint.first + curPoint.second * width];
			for (int i = -1; i <= 1; i++)
				for (int j = -1; j <= 1; j++)
				{
					if ((i + j) % 2 == 0) continue;
					std::pair<int, int> nextPoint(curPoint.first + i, curPoint.second + j);
					if (nextPoint.first >= 0 && nextPoint.first < width
						&& nextPoint.second >= 0 && nextPoint.second < height
						&& map->canWalkHere(nextPoint.first, nextPoint.second)
						&& distancemap[nextPoint.first + nextPoint.second * width] > curDistance + 1)
					{
						//float delta = std::max(abs((i + j) / 2.0f), abs((float)j - (float)i));
						//float delta = static_cast<float>(sqrt(i*i + j*j));
						distancemap[nextPoint.first + nextPoint.second * width] = curDistance + 1;
						q.push(nextPoint);
					}
				}
		}
	}
}


void Pathfinder::addHeat(sf::Vector2i pos, double value) {
	if (pos.x >= 0 && pos.x < width && pos.y >= 0 && pos.y < height) {
		heatmap[pos.x + pos.y*width] += value;
	}
}

float Pathfinder::getHeat(sf::Vector2i pos) {
	return getHeat(pos.x, pos.y);
}

float Pathfinder::getHeat(int x, int z) {
	if (x >= 0 && x < width && z >= 0 && z < height)
		return heatmap[x + z * width];
	else
		return FLT_MAX;
}

void Pathfinder::printHeat()
{
	for (int i = 0; i < heatmap.size(); i++) {
		if (i % map->getWidth() == 0) {
			std::cout << std::endl;
		}
		float h = getHeat(i % map->getWidth(), i / map->getWidth());
		if (h >= FLT_MAX - 10) {
			std::cout << " X  ";
			continue;
		}
		std::cout << h << (h < 9 ? (h >= 0 ? "   " : "  ") : (h <= 99 ? "  " : " "));

	}
}

void Pathfinder::LateUpdate()
{
	heatmap = distancemap;
	
}
