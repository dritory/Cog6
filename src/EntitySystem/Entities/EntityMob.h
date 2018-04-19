#pragma once
#include "../Entity.h"
#include "../InteractableEntity.h"
#include "../Pathfinder.h"
class EntityMob : public Entity{
public:
	EntityMob(EntitySystem* system, const EntityId& id);
	~EntityMob();

private:
	std::deque<sf::Vector3f>path;
	sf::Vector3f velocity;
	enum MobState {
		IDLE, MOVING
	} state;


	float speed = 2.0f;
	sf::Vector2i getTilePos();

	sf::Vector3i getBestDirection();
	 
	Pathfinder *pathFinder;

	sf::Vector3f normalize(const sf::Vector3f& source);

	int waitTimer = 0;
	sf::Vector3i lastDirection;

protected:
	void Update() override;
	std::string GetSpriteLocation() override { return "mob.png"; }
};

