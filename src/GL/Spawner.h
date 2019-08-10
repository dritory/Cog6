#pragma once
#include "..\PlayState.h"
#include "..\EntitySystem\Entities\EntityMob.h"

#include "../EntitySystem/Entities/EntityFodder.h"
#include "../EntitySystem/Entities/EntityTank.h"

#include "Taint.h"
class Spawner {
public:
	Spawner();
	~Spawner();
	template <class entity>
	struct mobtype {
		const entity type;
		int count = 0;
	};

	template <class entity>
	entity * AddToPool() {

		entity * ent = Game::Instance()->entitysystem->Add<entity>();
		mobpool.push_back(ent);
		return ent;
	}
	template <class entity>
	bool RemoveFromPool(entity * ent) {
		mobpool.erase(ent);
	}

	void update(sf::Time elapsed);

	std::vector<EntityMob *> & getUsedMobs() { return usedMobs; };

	void startNextWave();

	mobtype<EntityFodder> fodder{ EntityFodder(nullptr,0),0 };
	mobtype<EntityTank> tank{ EntityTank(nullptr,0),0 };

	template <class TYPE>
	bool forceSpawn(mobtype<TYPE> & m, float x, float y, float z) {

		for ( auto p = unusedMobs.begin(); p != unusedMobs.end(); p++ ) {
			TYPE* type = dynamic_cast<TYPE*> (*p);
			if ( type != nullptr ) { //the mob is of the same type

				Game::Instance()->entitysystem->ActivateEntity(*p);
				(*p)->SetPosition(sf::Vector3f(x, y, z));
				(*p)->SetHealthToMax();
				usedMobs.push_back(*p);
				p = unusedMobs.erase(p);
				m.count++;
				return true;
			}
		}

		TYPE* entity = AddToPool<TYPE>();
		entity->SetPosition(sf::Vector3f(x, y, z));
		entity->SetHealthToMax();
		usedMobs.push_back(entity);
		m.count++;
		return true;


	}


	template <class TYPE>
	//isocoords
	bool spawn(mobtype<TYPE> & m, float x, float y, float z) {


		if ( m.count < m.type.getSpawnNumber(wave, 1) ) {
			if ( Game::Instance()->tileSystem->pathfinder->isValidAt(x, z) ) {
				for ( auto p = unusedMobs.begin(); p != unusedMobs.end(); p++ ) {
					TYPE* type = dynamic_cast<TYPE*> (*p);
					if ( type != nullptr ) { //the mob is of the same type

						Game::Instance()->entitysystem->ActivateEntity(*p);
						(*p)->SetPosition(sf::Vector3f(x, y, z));
						(*p)->SetHealthToMax();
						usedMobs.push_back(*p);
						p = unusedMobs.erase(p);
						m.count++;
						return true;
					}
				}

				TYPE* entity = AddToPool<TYPE>();
				entity->SetPosition(sf::Vector3f(x, y, z));
				entity->SetHealthToMax();
				usedMobs.push_back(entity);
				m.count++;
				return true;
			}
		}
		return false;
	}


	void load();

	int getWave() {
		return wave;
	};

	Taint taint;


private:

	sf::Clock spawnerClock;
	sf::Clock waveClock;

	int waveInterval = 50;//in seconds
	int waveDuration = 20;//in seconds
	int spawnInterval = 2000; //in milliseconds

	int entityLimit = 2000;
	int wave = 0;

	std::vector<EntityMob *> unusedMobs;
	std::vector<EntityMob *> usedMobs;

	std::vector<EntityMob *> mobpool;



};

