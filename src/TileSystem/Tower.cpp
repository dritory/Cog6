#include "Tower.h"
#include "..\Game.h"
Tower::Tower(EntitySystem* system, const EntityId& id) : Building(system, id)
{
	

}


Tower::~Tower()
{
}

void Tower::Load(){
	
	Building::Load();

	SetHealth(300);
	maxHealth = 300;
	powerUsage = 1;
	heat = 10.0f;

	AddSubBuilding(0, 1, 0, Game::instance().getEntitySystem().Add<SubBuilding>("", "tower_a.png"));

}

void Tower::Update() {

	Building::Update();
}
