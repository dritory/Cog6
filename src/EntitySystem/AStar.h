#pragma once
#include <cstdlib>
#include <utility>
#include <SFML\Graphics.hpp>

#include <queue>
#include "..\TileSystem\TileMap.h"
class Node
{
	// current position
	int xPos;
	int yPos;
	// total distance already travelled to reach the node
	int level;
	// priority=level+remaining distance estimate
	int priority;  // smaller: higher priority
public:
	// Determine priority (in the priority queue)
	bool operator<(const Node & b) const;

	Node(int xp, int yp, int d, int p);

	int getxPos() const { return xPos; }
	int getyPos() const { return yPos; }
	int getLevel() const { return level; }
	int getPriority() const { return priority; }

	void updatePriority(const int & xDest, const int & yDest);

	// give better priority to going strait instead of diagonally
	void nextLevel(const int & i); // i: direction
	
	// Estimation function for the remaining distance to the goal.
	const int & estimate(const int & xDest, const int & yDest) const;
};

	

class AStar {
	
		
public:
	
	AStar();
	~AStar();
	
	// A-star algorithm.
	std::deque<sf::Vector3f> findPath(sf::Vector3i start, sf::Vector3i destination);


private:
	// Creating a shortcut for int, int pair type
	typedef std::pair<int, int> Pair;

	// Creating a shortcut for pair<int, pair<int, int>> type
	typedef std::pair<double, std::pair<int, int>> pPair;

	TileMap *map;

	static const int dir = 8;
	const int dx [dir] ={1, 1, 0, -1, -1, -1, 0, 1};
	const int dy [dir] ={0, 1, 1, 1, 0, -1, -1, -1};
	
};