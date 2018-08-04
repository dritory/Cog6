#pragma once
#include "Building.h"
#include "..\EntitySystem\Entities\EntityMob.h"
class Tower :
	public Building
{
public:
	Tower(EntitySystem* system, const EntityId& id);
	~Tower();
protected:
	virtual void Load();
	virtual void Update();
	virtual void Reset();
private:
	Entity * target;
};

