#include "Base.h"
#include "..\Game.h"

Base::Base(EntitySystem* system, const EntityId& id) : Building(system,id){
}


Base::~Base() {
	if(&Game::instance().getTileSystem() != nullptr && Game::instance().getTileSystem().pathfinder != NULL)
	if (Game::instance().getTileSystem().pathfinder->targetExistsAt(tileX,tileZ)) {
		Game::instance().getTileSystem().pathfinder->removeTarget(tileX, tileZ);
		Game::instance().getTileSystem().pathfinder->recalculateMap();
	}
}
bool Base::BindToTile(int x, int y, int z) {

	if (Building::BindToTile(x, y, z)) {
		
		Game::instance().getTileSystem().pathfinder->addTarget(x, z);
		return true;
	}
	return false;
}
void Base::Load(){
	
	maxHealth = 1000;
	SetHealth(maxHealth);
	powerUsage = -5;
	heat = 0.0f;

	AddSubBuilding(0, 0, 0, Game::instance().getEntitySystem().Add<SubBuilding>("", "block.png"));
	AddSubBuilding(1, 0, 0, Game::instance().getEntitySystem().Add<SubBuilding>("", "block.png"));
	AddSubBuilding(0, 0, 1, Game::instance().getEntitySystem().Add<SubBuilding>("", "block.png"));
	AddSubBuilding(1, 0, 1, Game::instance().getEntitySystem().Add<SubBuilding>("", "block.png"));
	
	AddSubBuilding(2, 0, -1, Game::instance().getEntitySystem().Add<SubBuilding>("", "slab.png"));
	AddSubBuilding(2, 0, 0, Game::instance().getEntitySystem().Add<SubBuilding>("", "slab.png"));
	AddSubBuilding(2, 0, 1, Game::instance().getEntitySystem().Add<SubBuilding>("", "slab.png"));

	AddSubBuilding(-1, 0, 2, Game::instance().getEntitySystem().Add<SubBuilding>("", "slab.png"));
	AddSubBuilding(0, 0, 2, Game::instance().getEntitySystem().Add<SubBuilding>("", "slab.png"));
	AddSubBuilding(1, 0, 2, Game::instance().getEntitySystem().Add<SubBuilding>("", "slab.png"));
	AddSubBuilding(2, 0, 2, Game::instance().getEntitySystem().Add<SubBuilding>("", "slab.png"));

	AddSubBuilding(-1, 0, -1, Game::instance().getEntitySystem().Add<SubBuilding>("", "slab.png"));
	AddSubBuilding(0, 0, -1, Game::instance().getEntitySystem().Add<SubBuilding>("", "slab.png"));
	AddSubBuilding(1, 0, -1, Game::instance().getEntitySystem().Add<SubBuilding>("", "slab.png"));

	AddSubBuilding(-1, 0, 0, Game::instance().getEntitySystem().Add<SubBuilding>("", "slab.png"));
	AddSubBuilding(-1, 0, 1, Game::instance().getEntitySystem().Add<SubBuilding>("", "slab.png"));

	Entity::Load();
}

void Base::Update() {
	
	if (isValid()) {
		Game::instance().getPlayer().addTM((int)(Game::instance().getPlayer().getPowerEfficienty()/10));
	}
	Building::Update();
}