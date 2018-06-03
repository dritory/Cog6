#pragma once
#include "Building.h"
class Tower :
	public Building
{
public:
	Tower(EntitySystem* system, const EntityId& id);
	~Tower();
protected:
	virtual void Load();
	virtual void Update();
};

