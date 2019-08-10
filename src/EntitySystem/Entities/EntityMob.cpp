#include "EntityMob.h"
#include <cstdlib>
#include <ctime>
#include "../../PlayState.h"
EntityMob::EntityMob(EntitySystem* system, const EntityId& id) : EntityAnimated(system, id) {
	
	maxHealth = 100;
	SetHealthToMax();

	playAnimation(idleAn);
}

EntityMob::~EntityMob() = default;

int EntityMob::getSpawnNumber(int round, int diff)
{
	return 0;
}

float EntityMob::getValue()
{
	return value;
}



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



sf::Vector3i EntityMob::getBestDirection() {
	if (waitTimer > 0) {
		return sf::Vector3i(0, 0, 0);
	}
	sf::Vector3f position = GetPosition();

	sf::Vector2i pos = pathFinder()->isoToGrid(GetPosition());
	int height = 0;
	int width = Game::Instance()->tileSystem->getWidth();
	float best = FLT_MAX;
	sf::Vector3i bestDirection(0, height, 0);
	bool stuck = false;

	for (int x = -1; x <= 1; x++) {
		for (int y = -1; y <= 1; y++) {

			if (pos.x + x >= 0 && pos.y + y >= 0 && pos.x + x < width && pos.y + y < width) {
				float heat = pathFinder()->getHeat(pos.x + x, pos.y + y);


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
				else if (pathFinder()->getHeatDifference(pos.x + x, pos.y + y) > 0.5f && (rand() % 1000) > 950) {
					waitTimer = std::rand() % 30 + 5;
				}
				
				//unstuck
				if (stuck && bestDirection == sf::Vector3i(0, height, 0)) {
					
					this->SetHealth(0);
				}

			}
		}
	}

	return bestDirection;
}


void EntityMob::Update() {

	if (updateClock.getElapsedTime().asMilliseconds() > 66) {

		sf::Vector3f position = GetPosition();

		if ( pathFinder()->isValid() ) {

			if ( hasPath ) {
				sf::Vector3f dir = normalize(sf::Vector3f(path.x - position.x, path.y -position.y ,  path.z - position.z));
				velocity = sf::Vector3f(dir.x, dir.y,  dir.z);
				if ( approximate(position, path, 5.0f) ) {
					hasPath = false;
					velocity = sf::Vector3f(0.0f, 0.0f, 0.0f);
				}
				if ( GetPosition().x < 0 ) {
					bool foo = false;
				}
			}
			else {

				lastDirection = getBestDirection();
				sf::Vector3i bestDirection = (sf::Vector3i)pathFinder()->gridToIso(lastDirection);
				if ( !(bestDirection.x == 0 && bestDirection.z == 0) ) {

					state = MOVING;
					sf::Vector2i pos = Game::Instance()->tileSystem->isoToTileCoord(GetPosition());

					TileEntity *e = Game::Instance()->tileSystem->getTileEntity(pos.x + lastDirection.x, 1 + lastDirection.y, pos.y + lastDirection.z);
					if ( e != nullptr ) {
						float interval = 1000.0f / (attackFreq * 60.0f);
						if ( attackClock.getElapsedTime().asMilliseconds() > interval ) {
							Attack(e);
							attackClock.restart();
							state = ATTACKING;
						}
					}
					else {
						
						path = (sf::Vector3f(bestDirection.x + position.x, bestDirection.y + position.y, bestDirection.z + position.z));
						hasPath = true;
					}
					
				}
				else {
					pathFinder()->addHeat(pathFinder()->isoToGrid(GetPosition()), 1.5f);
					state = IDLE;
				}

			}
			pathFinder()->addHeat(pathFinder()->isoToGrid(GetPosition()) + (sf::Vector2i(lastDirection.x, lastDirection.z)), heatModifier/2);

			pathFinder()->addHeat(pathFinder()->isoToGrid(GetPosition()), heatModifier);

			pathFinder()->addHeat(pathFinder()->isoToGrid(GetPosition()) - (sf::Vector2i(lastDirection.x, lastDirection.z)), heatModifier/2);

			/*
			//Generates heat in an 3x3 area, with most heat in the middle
			for (int x = -1; x <= 1; x++) {
				for (int y = -1; y <= 1; y++) {

					//pathFinder()->addHeat(pathFinder()->isoToGrid(GetPosition()) + sf::Vector2i(x, y), 1.0f / 100 * (5*abs(x) + 5*abs(y)+ 1));
				}
			}*/

			if ( waitTimer > 0 ) {
				waitTimer--;
			}

		}
		updateClock.restart();

		switch ( state ) {

		case ATTACKING:
			playAnimation(attackAn);
			break;

		case MOVING:
			playAnimation(walkAn);
			break;

		case IDLE:
		default:
			playAnimation(idleAn);

			break;
		}

	}
	EntityAnimated::Update();
}
void EntityMob::Reset()
{
	hasPath = false;
	velocity = sf::Vector3f(0,0,0);
	lastDirection = sf::Vector3i(0,0,0);
	waitTimer = 0;
	SetHealthToMax();
}
void EntityMob::Attack(TileEntity * e)
{
	if ( e != nullptr ) {
			e->damage(damage);
	}
}
void EntityMob::FixedUpdate(sf::Time elapsed) {
	sf::Vector3f position = GetPosition();
	if (pathFinder()->isValid()) {
		if (!approximate(velocity, sf::Vector3f(0, 0, 0), 0.001f)) {

			sf::Vector3f deltaS = sf::Vector3f(velocity.x * elapsed.asSeconds(), velocity.y * elapsed.asSeconds(), velocity.z * elapsed.asSeconds());
			SetPosition(GetPosition() + (sf::Vector3f)deltaS);

		}
	}
	if ( position.x < 0 ||position.z < 0 || position.x > Game::Instance()->tileSystem->getWidth_world() || position.z > Game::Instance()->tileSystem->getWidth_world() )
	{
		this->SetHealth(this->GetHealth() - 10);
	}
	Entity::FixedUpdate(elapsed);
}

Pathfinder * EntityMob::pathFinder()
{
	return Game::Instance()->tileSystem->pathfinder;
}
