#include "Building.h"
#include "..\Game.h"
#include "..\EntitySystem\EntitySystem.h"

Building::Building(EntitySystem* system, const EntityId& id) : TileEntity(system, id) 
{
	SetHealth(100);
	heat = 10.0f;
}


Building::~Building()
{
}



void Building::Update()
{
	if (heat != 0) {
		//Game::instance().getTileSystem().pathfinder->addHeat(sf::Vector2i(tileX,tileZ), heat);
	}
	if (GetHealth() == 0) {
		
		tileSystem->pathfinder->recalculateMap();
		GetSystem()->RemoveEntity(this);
	}
	
}
