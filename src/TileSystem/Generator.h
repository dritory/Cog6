#pragma once
#include "Building.h"
class Generator :
	public Building {
public:
	Generator(EntitySystem* system, const EntityId& id);
protected:
	virtual void Load();
	virtual void Update();
};

