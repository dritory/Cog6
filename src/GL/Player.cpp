#include "Player.h"
#include "..\Game.h"
#include "..\TileSystem\Building.h"
#include "..\TileSystem\TileEntity.h"
Player::Player() {
}


Player::~Player() {
}

void Player::build(int x, int y, int z)
{
	if (Game::instance().getTileSystem().isInBounds(x, y, z)) {
		Building *b;
		b = Game::instance().getEntitySystem().Add<Building>();

		if (!b->BindToTile(x, y, z)) {
			Game::instance().getEntitySystem().RemoveEntity(b);
			return;
		}
		else {
			//Game::instance().getTileSystem().pathfinder->recalculateMap();


		}
	}
}

void Player::Update()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {

		sf::Vector2i pos = Game::instance().getTileSystem().getMap(32).mouseToTile(Game::instance().getWindow());
		build(pos.x, 1, pos.y);
		
		Game::instance().getTileSystem().pathfinder->recalculateMap();
	}
}
