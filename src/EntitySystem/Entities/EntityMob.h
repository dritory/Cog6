#pragma once
#include "./EntityAnimated.h"
#include "../InteractableEntity.h"
#include "../Pathfinder.h"
#include "../../TileSystem/TileEntity.h"

class EntityMob : public EntityAnimated{
public:
	
	EntityMob(EntitySystem* system, const EntityId& id);
	~EntityMob();

	static int getSpawnNumber(int round, int diff);

	float getValue();

	void Reset() override;
protected:
	sf::Vector3f path;
	bool hasPath = false;
	enum MobState {
		IDLE, MOVING, ATTACKING,
	} state;

	Animation idleAn{10,16,32,66,0,0,true,true};
	Animation walkAn{ 10,16,32,66,0,3 * 8 * 32,true,true };
	Animation attackAn{ 10,16,32,66,0,1 * 8 * 32,false,true };


	float value = 10.0f;

	int speed = 100;

	float heatModifier = 0.6f;

	float damage;

	float attackFreq = 10; //per minute aka apm

	sf::Vector3i getBestDirection();

	virtual void FixedUpdate(sf::Time elapsed);
	 
	Pathfinder *pathFinder();

	sf::Vector3f normalize(const sf::Vector3f& source);

	int waitTimer = 0;

	sf::Clock attackClock;

	sf::Clock updateClock;
	sf::Vector3i lastDirection;

	

	void Attack(TileEntity *e);

	void Update() override;


	std::string GetSpriteLocation() override { return "sheet2.png"; }
};

