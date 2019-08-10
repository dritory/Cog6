#include "Base.h"
#include "..\PlayState.h"

Base::Base(EntitySystem* system, const EntityId& id) : Building(system,id){
}


Base::~Base() {
	if(&Game::Instance()->tileSystem != nullptr && Game::Instance()->tileSystem->pathfinder != NULL)
	if (Game::Instance()->tileSystem->pathfinder->targetExistsAt(tileX,tileZ)) {
		Game::Instance()->tileSystem->pathfinder->removeTarget(tileX, tileZ);
		Game::Instance()->tileSystem->pathfinder->recalculateMap();
	}
}
bool Base::BindToTile(int x, int y, int z) {

	if (Building::BindToTile(x, y, z)) {
		
		Game::Instance()->tileSystem->pathfinder->addTarget(x, z);
		return true;
	}
	return false;
}
void Base::Load(){
	
	maxHealth = 1000;
	SetHealth(maxHealth);
	powerUsage = -5;
	heat = 0.0f;

	AddSubBuilding(0, 0, 0, Game::Instance()->entitysystem->Add<SubBuilding>("", "block.png"));
	AddSubBuilding(1, 0, 0, Game::Instance()->entitysystem->Add<SubBuilding>("", "block.png"));
	AddSubBuilding(0, 0, 1, Game::Instance()->entitysystem->Add<SubBuilding>("", "block.png"));
	AddSubBuilding(1, 0, 1, Game::Instance()->entitysystem->Add<SubBuilding>("", "block.png"));
	
	AddSubBuilding(2, 0, -1, Game::Instance()->entitysystem->Add<SubBuilding>("", "slab.png"));
	AddSubBuilding(2, 0, 0, Game::Instance()->entitysystem->Add<SubBuilding>("", "slab.png"));
	AddSubBuilding(2, 0, 1, Game::Instance()->entitysystem->Add<SubBuilding>("", "slab.png"));

	AddSubBuilding(-1, 0, 2, Game::Instance()->entitysystem->Add<SubBuilding>("", "slab.png"));
	AddSubBuilding(0, 0, 2, Game::Instance()->entitysystem->Add<SubBuilding>("", "slab.png"));
	AddSubBuilding(1, 0, 2, Game::Instance()->entitysystem->Add<SubBuilding>("", "slab.png"));
	AddSubBuilding(2, 0, 2, Game::Instance()->entitysystem->Add<SubBuilding>("", "slab.png"));

	AddSubBuilding(-1, 0, -1, Game::Instance()->entitysystem->Add<SubBuilding>("", "slab.png"));
	AddSubBuilding(0, 0, -1, Game::Instance()->entitysystem->Add<SubBuilding>("", "slab.png"));
	AddSubBuilding(1, 0, -1, Game::Instance()->entitysystem->Add<SubBuilding>("", "slab.png"));

	AddSubBuilding(-1, 0, 0, Game::Instance()->entitysystem->Add<SubBuilding>("", "slab.png"));
	AddSubBuilding(-1, 0, 1, Game::Instance()->entitysystem->Add<SubBuilding>("", "slab.png"));

	Entity::Load();
}

void Base::Update() {
	
	if (isValid()) {
		if ( genClock.getElapsedTime().asMilliseconds() > 500 ) {
			Game::Instance()->player->addTM((int) (Game::Instance()->player->getPowerEfficienty() / 10));
			genClock.restart();
		}
	}
	Building::Update();
}