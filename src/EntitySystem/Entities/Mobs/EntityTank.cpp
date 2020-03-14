#include "EntityTank.h"
#include "../../../PlayState.h"
void EntityTank::FixedUpdate(sf::Time elapsed)
{
	EntityMob::FixedUpdate(elapsed);
}

EntityTank::EntityTank(EntitySystem * system, const EntityId & id) : EntityMob(system, id)
{
	speed = 70;
	maxHealth = 500;
	attackFreq = 10;
	damage = 10;
	heatModifier = 1.2f;
	setColor(sf::Color::Red);
	setScale(sf::Vector2f(1.8f, 1.5f));
	setOrigin(sf::Vector2f(0, 16.0f));
}

EntityTank::~EntityTank()
{

}

int EntityTank::getSpawnNumber(int round, int diff)
{

	int rsp = (int) ((0.15 * round) * (24 + 6 * (diff)));
	return round % 5 == 0 ? rsp : 0;

}

void EntityTank::Update()
{
	EntityMob::Update();
}
