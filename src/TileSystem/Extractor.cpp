#include "Extractor.h"
#include "..\Game.h"

Extractor::Extractor(EntitySystem* system, const EntityId& id) : Building(system,id){
}


Extractor::~Extractor() {
	if(&Game::instance().getTileSystem() != nullptr)
	if (Game::instance().getTileSystem().pathfinder->targetExistsAt(tileX,tileZ)) {
		Game::instance().getTileSystem().pathfinder->removeTarget(tileX, tileZ);
		Game::instance().getTileSystem().pathfinder->recalculateMap();
	}
}
bool Extractor::BindToTile(int x, int y, int z) {

	if (Building::BindToTile(x, y, z)) {
		
		Game::instance().getTileSystem().pathfinder->addTarget(x, z);
		return true;
	}
	return false;
}
void Extractor::Load(){
	
	maxHealth = 500;
	SetHealth(maxHealth);
	powerUsage = 35;
	heat = 0.0f;

	AddSubBuilding(0, 0, 0, Game::instance().getEntitySystem().Add<SubBuilding>("", "extractor_d.png"));
	AddSubBuilding(1, 0, 0, Game::instance().getEntitySystem().Add<SubBuilding>("", "extractor_c.png"));
	AddSubBuilding(0, 0, 1, Game::instance().getEntitySystem().Add<SubBuilding>("", "extractor_b.png"));
	AddSubBuilding(1, 0, 1, Game::instance().getEntitySystem().Add<SubBuilding>("", "extractor_a.png"));
	
	

	Entity::Load();
}

void Extractor::Update() {
	
	if (isValid()) {
		Game::instance().getPlayer().addTM((int)(Game::instance().getPlayer().getPowerEfficienty()/10));
	}
	Building::Update();
}