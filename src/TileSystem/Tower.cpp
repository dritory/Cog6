#include "Tower.h"
#include "..\PlayState.h"
Tower::Tower(EntitySystem* system, const EntityId& id) : Building(system, id)
{
	

}


Tower::~Tower()
{
}

void Tower::Load(){

	SetHealth(300);
	maxHealth = 300;
	powerUsage = 1;
	heat = 0.1f;
	AddSubBuilding(0, 0, 0);
	AddSubBuilding(0, 1, 0, "tower_a.png");

	Entity::Load();
}

void Tower::Update() {

	if ( target == nullptr || !target->isAlive() || target->Deactivated()) {

		target = Game::Instance()->rangehelper->getEntity<EntityMob>(tileX, tileZ, 10.0f, RangeHelper::CLOSEST);
	
	}
	else
	{
		target->SetHealth(target->GetHealth() - 1);
	}
	/*
	auto list = Game::Instance()->rangehelper->entitiesInRange(tileX,tileZ, 10);
	if ( list.size() > 0 ) {
		for ( auto *e : list ) {

			e->SetHealth(e->GetHealth() - 1);
		}
	}
	*/
	Building::Update();
}

void Tower::Reset()
{
	target = nullptr;
}
