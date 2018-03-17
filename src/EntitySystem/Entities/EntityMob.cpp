#include "EntityMob.h"
#include <random>
#include <ctime>
#include "../../Game.h"
EntityMob::EntityMob(EntitySystem* system, const EntityId& id) : Entity(system, id) {
	pathFinder = &Game::instance().getTileSystem().pathfinder;
	//path = astar.findPath(sf::Vector3i(1, 1, 1), sf::Vector3i(rand() % 32, 1, rand() % 32));
}

EntityMob::~EntityMob() = default;


sf::Vector3f EntityMob::normalize(const sf::Vector3f& source) {
	return sf::Vector3f((source.x > 0 ? speed : (source.x < 0) ? -speed : 0), (source.y > 0 ? speed : (source.y < 0) ? -speed : 0), (source.z > 0 ? speed : (source.z < 0) ? -speed : 0));

	float length = sqrt((source.x * source.x) + (source.y * source.y) + (source.z * source.z));
	if (length != 0)
		return sf::Vector3f(source.x / length, source.y / length, source.z / length);
	else
		return source;
}

sf::Vector2i EntityMob::getTilePos() {

	return Game::instance().getTileSystem().isoToTileCoord(GetPosition());
}

sf::Vector3i EntityMob::getBestDirection() {
	sf::Vector2i pos = getTilePos();
	int height = 0;
	float best = FLT_MAX;
	sf::Vector3i bestDirection(0, 0, 0);
	for (int x = -1; x <= 1; x++) {
		for (int y = -1; y <= 1; y++) {

			float heat = pathFinder->getHeat(pos.x + x, pos.y + y);

			if (x == 0 && y == 0) {
				if (heat == 0) {
					
					this->SetPosition(sf::Vector3f(0, 32*1, 0));
					return sf::Vector3i(0, 0, 0);
				}
				continue;
			}
			if (heat < best || (heat != FLT_MAX && heat == best && rand() % 100 > 75) ) {

				best = heat;
				bestDirection = sf::Vector3i(x, height, y);
			}

		}
	}

	return bestDirection;
}

void EntityMob::Update() {
	sf::Vector3f position = GetPosition();



	if (path.size() > 0) {

		velocity = normalize(path[0] - position);
		if ((sf::Vector3i)position == (sf::Vector3i)path[0]) {
			path.pop_front();
			velocity = sf::Vector3f(0, 0, 0);
		}

	}
	else {
		
		sf::Vector3f dir = Game::instance().getTileSystem().tileToIsoCoord(getBestDirection());
		if (!(dir.x == 0 && dir.z == 0)) {

			path.push_back(sf::Vector3f(dir.x + position.x, dir.y + position.y, dir.z + position.z));
		}
	}

	SetPosition(GetPosition() + velocity);
	pathFinder->addHeat(sf::Vector2i(getTilePos().x, getTilePos().y), 1);
}
