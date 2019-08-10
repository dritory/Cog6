#pragma once
#include "..\PlayState.h"
class RangeHelper {

public:


	enum Priority
	{
		CLOSEST = 2,
		FURTHEST = -2,
		STRONGEST = 1,
		WEAKEST = -1,
		RANDOM = 0,
	};

	RangeHelper(int width, int length);

	void addEntity(int x, int z, Entity * entity);

	void flush();

	void Update(sf::Time elapsed);

	bool isInRange(Entity * entity,int x, int z, float range);
	


	std::vector<Entity*> getEntities(int x, int z);
	template<class TYPE>
	std::vector<Entity *> entitiesInRange(int x, int z, float range) {
		int tsize = Game::Instance()->tileSystem->getTileSize();
		std::vector<Entity *> temp;

		for ( auto e : Game::Instance()->spawner->getUsedMobs() ) {
			TYPE* type = dynamic_cast<TYPE*> (*e);
			if ( type != nullptr ) { //the mob is of the same type
				sf::Vector3f pos = e->GetPosition();
				float dx = ((pos.x / tsize) - x);
				float dy = ((pos.z / tsize) - z);
				float distance = (dx*dx + dy * dy);
				if ( distance <= range * range ) {
					temp.push_back(e);
				}
			}
		}
		return temp;
	};

	template<class TYPE>
	Entity * getEntity(int x, int z, float range, Priority priority = RANDOM) {
		switch ( priority ) {
		case CLOSEST:
			return getClosestEntity<TYPE>(x, z, range);
		case FURTHEST:
			return getFurthestEntity<TYPE>(x, z, range);
		case STRONGEST:
			return getStrongestEntity<TYPE>(x, z, range);
		case WEAKEST:
			return getWeakestEntity<TYPE>(x, z, range);
		default:
			int tsize = Game::Instance()->tileSystem->getTileSize();
			for ( auto e : Game::Instance()->spawner->getUsedMobs() ) {
				TYPE* type = dynamic_cast<TYPE*> (e);
				if ( type != nullptr ) { //the mob is of the same type
					sf::Vector3f pos = e->GetPosition();
					float dx = ((pos.x / tsize) - x);
					float dy = ((pos.z / tsize) - z);
					float distance = (dx*dx + dy * dy);
					if ( distance <= range * range ) {

						return e;
					}
				}
			}

		}
		return nullptr;

	};
	template<class TYPE>
	Entity * getClosestEntity(int x, int z, float range) {
		Entity * entity = nullptr;
		int dist = range * range;
		int tsize = Game::Instance()->tileSystem->getTileSize();
		for ( auto e : Game::Instance()->spawner->getUsedMobs() ) {
			TYPE* type = dynamic_cast<TYPE*> (e);
			if ( type != nullptr ) { //the mob is of the same type

				sf::Vector3f pos = e->GetPosition();
				float dx = ((pos.x / tsize) - x);
				float dy = ((pos.z / tsize) - z);
				float distance = (dx*dx + dy * dy);
				if ( distance <= range * range ) {

					if ( distance < dist ) {

						entity = e;
						dist = distance;
					}
				}

			}
		}
		return entity;
	};
	template<class TYPE>
	Entity * getFurthestEntity(int x, int z, float range) {
		Entity * entity = nullptr;
		int dist = 0;
		int tsize = Game::Instance()->tileSystem->getTileSize();
		for ( auto e : Game::Instance()->spawner->getUsedMobs() ) {
			TYPE* type = dynamic_cast<TYPE*> (e);
			if ( type != nullptr ) { //the mob is of the same type

				sf::Vector3f pos = e->GetPosition();
				float dx = ((pos.x / tsize) - x);
				float dy = ((pos.z / tsize) - z);
				float distance = (dx*dx + dy * dy);
				if ( distance <= range * range ) {

					if ( distance > dist ) {

						entity = e;
						dist = distance;
					}

				}
			}
		}
		return entity;
	};
	template<class TYPE>
	Entity * getStrongestEntity(int x, int z, float range) {
		Entity * entity = nullptr;
		int health = 0;
		int tsize = Game::Instance()->tileSystem->getTileSize();
		for ( auto e : Game::Instance()->spawner->getUsedMobs() ) {
			TYPE* type = dynamic_cast<TYPE*> (e);
			if ( type != nullptr ) { //the mob is of the same type

				sf::Vector3f pos = e->GetPosition();
				float dx = ((pos.x / tsize) - x);
				float dy = ((pos.z / tsize) - z);
				float distance = (dx*dx + dy * dy);
				if ( distance <= range * range ) {
					int h = e->GetHealth();
					if ( h > health ) {
						entity = e;
						health = h;
					}

				}
			}
		}
		return entity;
	};
	template<class TYPE>
	Entity * getWeakestEntity(int x, int z, float range) {
		Entity * entity = nullptr;
		int health = INT_MAX;
		int tsize = Game::Instance()->tileSystem->getTileSize();
		for ( auto e : Game::Instance()->spawner->getUsedMobs() ) {
			TYPE* type = dynamic_cast<TYPE*> (e);
			if ( type != nullptr ) { //the mob is of the same type

				sf::Vector3f pos = e->GetPosition();
				float dx = ((pos.x / tsize) - x);
				float dy = ((pos.z / tsize) - z);
				float distance = (dx*dx + dy * dy);
				if ( distance <= range * range ) {
					int h = e->GetHealth();
					if ( h < health ) {
						entity = e;
						health = h;
					}

				}
			}
		}
		return entity;
	};

	


private:
	std::unordered_map<int, std::vector<Entity * >> entities;
	std::map<float, std::vector<sf::Vector2i>> ranges;

	int width;
	int lenght;

	std::vector<sf::Vector2i> getRangeArray(float range);

	int index(int x, int z) { return x + z * width; };

};