#include "AStar.h"
#include <algorithm>
#include <set>
#include "..\PlayState.h"
Node::Node(int xp, int yp, int d, int p) {
	xPos = xp; yPos = yp; level = d; priority = p;
}

void Node::updatePriority(const int & xDest, const int & yDest) {
	priority = level + estimate(xDest, yDest) * 10; //A*
}

void Node::nextLevel(const int & i) {
	level += (i % 2 == 0 ? 10 : 14);
}

const int & Node::estimate(const int & xDest, const int & yDest) const {
	static int xd, yd, d;
	xd = xDest - xPos;
	yd = yDest - yPos;

	// Euclidian Distance
	//When to use this heuristic? – When we are allowed to move in any directions.
	//d = static_cast<int>(sqrt(xd*xd + yd * yd));

	// Manhattan distance
	//When to use this heuristic? – When we are allowed to move only in four directions only (right, left, top, bottom)
	//d=abs(xd)+abs(yd);

	// Chebyshev distance
	//When to use this heuristic? – When we are allowed to move in eight directions only
	d = std::max(abs(xd), abs(yd));

	return(d);
}

bool Node::operator<(const Node & b) const {
	return this->getPriority() > b.getPriority();
}


AStar::AStar() {
}

AStar::~AStar() {
	map = nullptr;
}
//takes in 2d coords
std::deque<sf::Vector3f> AStar::findPath(sf::Vector3i start, sf::Vector3i destination) {
	
	map = &Game::Instance()->tileSystem->getMap(start.y * 32);
	
	//changes the z and y
	start = sf::Vector3i(start.x, start.z, start.y);
	destination = sf::Vector3i(destination.x, destination.z, destination.y);

	std::priority_queue<Node> pq[2]; // list of open (not-yet-tried) nodes
	int pqi; // pq index
	Node* n0;
	Node* m0;
	int i, j, x, y, xdx, ydy;
	char c;
	pqi = 0;

	const int n = map->getWidth();
	const int m = map->getHeight();
	

	int* closed_nodes_map = new int[n*m]; // map of closed (tried-out) nodes
	int* open_nodes_map= new int[n*m]; // map of open (not-yet-tried) nodes
	int* dir_map= new int[n*m]; // map of directions

	// reset the node maps
	for (y = 0; y < m; y++) {
		for (x = 0; x < n; x++) {
			closed_nodes_map[x + n*y] = 0;
			open_nodes_map[x + n*y] = 0;
		}
	}

	// create the start node and push into list of open nodes
	n0 = new Node(start.x, start.y, 0, 0);
	n0->updatePriority(destination.x, destination.y);
	pq[pqi].push(*n0);
	open_nodes_map[x + n*y] = n0->getPriority(); // mark it on the open nodes map

											  // A* search
	while (!pq[pqi].empty()) {
		// get the current node w/ the highest priority
		// from the list of open nodes
		n0 = new Node(pq[pqi].top().getxPos(), pq[pqi].top().getyPos(),
			pq[pqi].top().getLevel(), pq[pqi].top().getPriority());

		x = n0->getxPos(); y = n0->getyPos();

		pq[pqi].pop(); // remove the node from the open list
		open_nodes_map[x + n*y] = 0;
		// mark it on the closed nodes map
		closed_nodes_map[x + n*y] = 1;

		// quit searching when the goal state is reached
		//if((*n0).estimate(xFinish, yFinish) == 0)
		if (x == destination.x && y == destination.y) {
			// generate the path from finish to start
			// by following the directions
			std::deque<sf::Vector3f>path;
			int oldDir = 100, lastX = x,lastY = y;
			while (!(x == start.x && y == start.y)) {
				j = dir_map[x + n*y];
				
					sf::Vector2f v = map->tileToWorld(sf::Vector2i(x, y));
					path.push_front(sf::Vector3f(v.x, start.y*map->getTileSize().y,v.y));
				
				lastX = x;
				lastY = y;
				oldDir = j;

				x += dx[j];
				y += dy[j];

			}

			// garbage collection
			delete n0;
			// empty the leftover nodes
			while (!pq[pqi].empty()) pq[pqi].pop();
			return path;
		}

		// generate moves (child nodes) in all possible directions

		for (i = 0; i < dir; i++) {
			xdx = x + dx[i]; ydy = y + dy[i];

			if (!(xdx<0 || xdx>n - 1 || ydy<0 || ydy>m - 1 ||!map->canWalkHere(xdx,ydy)
				|| closed_nodes_map[xdx +n*ydy] == 1)) {
				// generate a child Node
				m0 = new Node(xdx, ydy, n0->getLevel(),
					n0->getPriority());
				m0->nextLevel(i);
				m0->updatePriority(destination.x, destination.y);

				// if it is not in the open list then add into that
				if (open_nodes_map[xdx +n*ydy] == 0) {
					open_nodes_map[xdx +n*ydy] = m0->getPriority();
					pq[pqi].push(*m0);
					// mark its parent node direction
					dir_map[xdx +n*ydy] = (i + dir / 2) % dir;
				}
				else if (open_nodes_map[xdx +n*ydy] > m0->getPriority()) {
					// update the priority info
					open_nodes_map[xdx +n*ydy] = m0->getPriority();
					// update the parent direction info
					dir_map[xdx +n*ydy] = (i + dir / 2) % dir;

					// replace the node
					// by emptying one pq to the other one
					// except the node to be replaced will be ignored
					// and the new node will be pushed in instead
					while (!(pq[pqi].top().getxPos() == xdx &&
						pq[pqi].top().getyPos() == ydy)) {
						pq[1 - pqi].push(pq[pqi].top());
						pq[pqi].pop();
					}
					pq[pqi].pop(); // remove the wanted node

								   // empty the larger size pq to the smaller one
					if (pq[pqi].size() > pq[1 - pqi].size()) pqi = 1 - pqi;
					while (!pq[pqi].empty()) {
						pq[1 - pqi].push(pq[pqi].top());
						pq[pqi].pop();
					}
					pqi = 1 - pqi;
					pq[pqi].push(*m0); // add the better node instead
				}
				else delete m0; // garbage collection
			}
		}
		delete n0; // garbage collection
	}
	delete closed_nodes_map, open_nodes_map, dir_map;

	return std::deque<sf::Vector3f>(); // no route found
}
