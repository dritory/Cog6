#include "EntityMob.h"
#include <cstdlib>
#include <ctime>
#include "../../Game.h"
EntityMob::EntityMob(EntitySystem* system, const EntityId& id) : Entity(system, id) {
	pathFinder = Game::instance().getTileSystem().pathfinder;
	
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
	if (waitTimer > 0)
		return sf::Vector3i(0, 0, 0);
	sf::Vector2i pos = pathFinder->isoToGrid(GetPosition());
	int height = 0;
	float best = FLT_MAX;
	sf::Vector3i bestDirection(0, height, 0);
	for (int x = -1; x <= 1; x++) {
		for (int y = -1; y <= 1; y++) {

			float heat = pathFinder->getHeat(pos.x + x, pos.y + y);

			if (x == 0 && y == 0) {
				if (heat == 0 || heat == FLT_MAX) {

					this->SetPosition(sf::Vector3f(4, 32 * 1, 4+ (std::rand() % Game::instance().getTileSystem().getWidth())*Game::instance().getTileSystem().getTileSize() ));
					return sf::Vector3i(0, 0, 0);
				}
				continue;
			}
			if (heat < best || (heat != FLT_MAX && (int)heat == (int)best && lastDirection == sf::Vector3i(x, height, y))) {//|| (heat != FLT_MAX && rand() % 1000 > 998)) {

				best = heat;
				bestDirection = sf::Vector3i(x, height, y);
			}
			else if (pathFinder->getHeatDifference(pos.x + x, pos.y + y) > 0.5f && rand() % 1000 > 900) {
				waitTimer = std::rand() % 30 + 5;
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
		sf::Vector3i bestDirection = getBestDirection();
		lastDirection = (sf::Vector3i)pathFinder->gridToIso(bestDirection);
		if (!(lastDirection.x == 0 && lastDirection.z == 0)) {

			sf::Vector2i pos = Game::instance().getTileSystem().isoToTileCoord(GetPosition());

			TileEntity *e = Game::instance().getTileSystem().getTileEntity(pos.x + bestDirection.x, 1 + bestDirection.y, pos.y + bestDirection.z);
			if (e != nullptr) {
				e->damage(1);
			}
			else {
				path.push_back(sf::Vector3f(lastDirection.x + position.x, lastDirection.y + position.y, lastDirection.z + position.z));
			}
		}
	}

	SetPosition(GetPosition() + velocity);
	pathFinder->addHeat(pathFinder->isoToGrid(GetPosition()), 0.05f);

	for (int x = -1; x <= 1; x++) {
		for (int y = -1; y <= 1; y++) {

			//pathFinder->addHeat(pathFinder->isoToGrid(GetPosition()) + sf::Vector2i(x, y), 1.0f / 10 * ((abs(x) + abs(y) + 1)));
		}
	}
	if (waitTimer > 0)
		waitTimer--;



}
