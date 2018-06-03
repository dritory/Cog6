#include "Generator.h"
#include "..\Game.h"

Generator::Generator(EntitySystem* system, const EntityId& id) : Building(system,id){
}

void Generator::Load(){
	
	maxHealth = 300;
	SetHealth(maxHealth);
	powerUsage = -10;
	heat = 0.0f;

	AddSubBuilding(0, 0, 0, Game::instance().getEntitySystem().Add<SubBuilding>("", "generator.png"));
	
	

	Entity::Load();
}

void Generator::Update() {
	



	Building::Update();
}