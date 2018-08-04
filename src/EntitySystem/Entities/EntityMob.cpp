#include "EntityMob.h"
#include <cstdlib>
#include <ctime>
#include "../../Game.h"
EntityMob::EntityMob(EntitySystem* system, const EntityId& id) : Entity(system, id) {
	pathFinder = Game::instance().getTileSystem().pathfinder;
	maxHealth = 100;
	SetHealthToMax();
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

bool approximate(sf::Vector3f A, sf::Vector3f B, float epsilon) {
	if (abs(A.x - B.x) < epsilon && abs(A.y - B.y) < epsilon && abs(A.z - B.z) < epsilon) {
		return true;
	}
	return false;
}

sf::Vector2i EntityMob::getTilePos() {

	return Game::instance().getTileSystem().isoToTileCoord(GetPosition());
}


sf::Vector3i EntityMob::getBestDirection() {
	if (waitTimer > 0) {
		return sf::Vector3i(0, 0, 0);
	}
	sf::Vector3f position = GetPosition();
	if ( position.x < 0 ) {
		bool foo = false;
	}
	sf::Vector2i pos = pathFinder->isoToGrid(GetPosition());
	int height = 0;
	int width = Game::instance().getTileSystem().getWidth();
	float best = FLT_MAX;
	sf::Vector3i bestDirection(0, height, 0);
	bool stuck = false;

	for (int x = -1; x <= 1; x++) {
		for (int y = -1; y <= 1; y++) {

			if (pos.x + x >= 0 && pos.y + y >= 0 && pos.x + x < width && pos.y + y < width) {
				float heat = pathFinder->getHeat(pos.x + x, pos.y + y);


				if (x == 0 && y == 0) {
					if (heat == 0) {


						return sf::Vector3i(0, 0, 0);
					}
					if (heat == FLT_MAX || isinf(heat)) {
						stuck = true;
					}
					continue;
				}
				//moving up and down is faster than moving side to side
				if (x == y && heat != FLT_MAX) {
					heat -= 0.5f;
				}
				//Also prefer to move in the same direction as opposite to changing direction
				if (lastDirection == sf::Vector3i(x, height, y)) {
					heat -= 1.5f;
				}
				//chooses the lowest heat location to move to

				if (heat < best) {//|| (heat != FLT_MAX && rand() % 1000 > 998)) {

					best = heat;
					bestDirection = sf::Vector3i(x, height, y);
				}
				//Makes the mob wait a bit if there is lots of heat going about
				else if (pathFinder->getHeatDifference(pos.x + x, pos.y + y) > 0.5f && (rand() % 1000) > 950) {
					waitTimer = std::rand() % 30 + 5;
				}
				
				//unstuck
				if (stuck && bestDirection == sf::Vector3i(0, height, 0)) {
					bestDirection = sf::Vector3i(x, height, y);
				}

			}
		}
	}

	return bestDirection;
}
void EntityMob::Update() {
	sf::Vector3f position = GetPosition();

	if (pathFinder->isValid()) {

		if (path.size() > 0) {


			if (approximate(position,path[0],5.0f)) {
				path.pop_front();
				velocity = sf::Vector3f(0.0f, 0.0f, 0.0f);
			}
			if ( GetPosition().x < 0 ) {
				bool foo = false;
			}
		}
		else {
			
			lastDirection = getBestDirection();
			sf::Vector3i bestDirection = (sf::Vector3i)pathFinder->gridToIso(lastDirection);
			if (!(bestDirection.x == 0 && bestDirection.z == 0)) {

				sf::Vector2i pos = Game::instance().getTileSystem().isoToTileCoord(GetPosition());

				TileEntity *e = Game::instance().getTileSystem().getTileEntity(pos.x + lastDirection.x, 1 + lastDirection.y, pos.y + lastDirection.z);
				if (e != nullptr) {
					e->damage(1);
				}
				else {
					velocity = sf::Vector3f(speed * lastDirection.x, speed *lastDirection.y, speed * lastDirection.z);
					path.push_back(sf::Vector3f(bestDirection.x + position.x, bestDirection.y + position.y, bestDirection.z + position.z));
				}
			}
			else {
				pathFinder->addHeat(pathFinder->isoToGrid(GetPosition()), 1.5f);
			}

		}
		pathFinder->addHeat(pathFinder->isoToGrid(GetPosition()) + (sf::Vector2i(lastDirection.x, lastDirection.z)), 0.3f);

		pathFinder->addHeat(pathFinder->isoToGrid(GetPosition()), 0.6f);

		pathFinder->addHeat(pathFinder->isoToGrid(GetPosition()) - (sf::Vector2i(lastDirection.x, lastDirection.z)), 0.3f);

		/*
		//Generates heat in an 3x3 area, with most heat in the middle
		for (int x = -1; x <= 1; x++) {
			for (int y = -1; y <= 1; y++) {

				//pathFinder->addHeat(pathFinder->isoToGrid(GetPosition()) + sf::Vector2i(x, y), 1.0f / 100 * (5*abs(x) + 5*abs(y)+ 1));
			}
		}*/
		if (waitTimer > 0) {
			waitTimer--;
		}

	}
	
}
void EntityMob::Reset()
{
	path.clear();
	velocity = sf::Vector3f();
	lastDirection = sf::Vector3i();
	waitTimer = 0;
	SetHealthToMax();
}
void EntityMob::FixedUpdate() {
	if (pathFinder->isValid()) {

		if (!approximate(velocity, sf::Vector3f(0, 0, 0), 0.001f)) {
			SetPosition(GetPosition() + (sf::Vector3f)velocity);

		}
	}
	Entity::FixedUpdate();
}
