#pragma once
#include "Building.h"
class Base :
	public Building {
public:
	Base(EntitySystem* system, const EntityId& id);
	~Base();

	virtual bool BindToTile(int x, int y, int z);
protected:
	virtual void Load();
	virtual void Update();

private:

	sf::Clock genClock;
};

