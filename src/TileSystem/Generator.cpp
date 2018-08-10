#include "Generator.h"
#include "..\PlayState.h"

Generator::Generator(EntitySystem* system, const EntityId& id) : Building(system,id){
}

void Generator::Load(){
	
	maxHealth = 300;
	SetHealth(maxHealth);
	powerUsage = -10;
	heat = 0.0f;

	AddSubBuilding(0, 1, 0, Game::Instance()->entitysystem->Add<SubBuilding>("", "generator.png"));
	
	AddSubBuilding(0, 0, 0, Game::Instance()->entitysystem->Add<SubBuilding>("", "block.png"));

	AddSubBuilding(-1, 0, -1, Game::Instance()->entitysystem->Add<SubBuilding>("", "slab.png"));
	AddSubBuilding(-1, 0, 0, Game::Instance()->entitysystem->Add<SubBuilding>("", "slab.png"));
	AddSubBuilding(-1, 0, 1, Game::Instance()->entitysystem->Add<SubBuilding>("", "slab.png"));
	AddSubBuilding(0, 0, -1, Game::Instance()->entitysystem->Add<SubBuilding>("", "slab.png"));
	AddSubBuilding(1, 0, -1, Game::Instance()->entitysystem->Add<SubBuilding>("", "slab.png"));
	AddSubBuilding(0, 0, 1, Game::Instance()->entitysystem->Add<SubBuilding>("", "slab.png"));

	AddSubBuilding(1, 0, 0, Game::Instance()->entitysystem->Add<SubBuilding>("", "slab.png"));
	AddSubBuilding(1, 0, 1, Game::Instance()->entitysystem->Add<SubBuilding>("", "slab.png"));


	Entity::Load();
}

void Generator::Update() {
	



	Building::Update();
}