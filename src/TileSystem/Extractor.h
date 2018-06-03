#pragma once
#include "Building.h"
class Extractor :
	public Building {
public:
	Extractor(EntitySystem* system, const EntityId& id);
	~Extractor();

	virtual bool BindToTile(int x, int y, int z);
protected:
	virtual void Load();
	virtual void Update();
};

