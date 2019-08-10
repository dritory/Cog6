#include "EntityFodder.h"

void EntityFodder::FixedUpdate(sf::Time elapsed)
{
	EntityMob::FixedUpdate(elapsed);
}

EntityFodder::EntityFodder(EntitySystem * system, const EntityId & id) : EntityMob(system,id)
{
	speed = 100;
	maxHealth = 100;
	attackFreq = 60;
	damage = 1;
	setScale(sf::Vector2f(1.0f, 1.0f));
	

}

int EntityFodder::getSpawnNumber(int round, int diff)
{
	int rsp = (int) ((0.15 * round) * (50 + 10 * (diff)));
	return rsp;
}

EntityFodder::~EntityFodder()
{

}

void EntityFodder::Update()
{
	EntityMob::Update();
}
