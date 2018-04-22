#include "Player.h"
#include "..\Game.h"
#include "..\TileSystem\Building.h"
#include "..\TileSystem\TileEntity.h"
Player::Player() {
}


Player::~Player() {
}

bool Player::build(int x, int y, int z)
{
	if (Game::instance().getTileSystem().isInBounds(x, y, z)) {
		Building *b = Game::instance().getEntitySystem().Add<Building>();

		if (!b->BindToTile(x, y, z) && b != nullptr) {
			Game::instance().getEntitySystem().RemoveEntity(b);
			return false;
		}
		else {
			//Game::instance().getTileSystem().pathfinder->recalculateMap();

			return true;
		}
	}
}

void Player::Update()
{
	static bool oldKeyState = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {// && !oldKeyState) {

		sf::Vector2i pos = Game::instance().getTileSystem().getMap(32).mouseToTile(Game::instance().getWindow());
		if (build(pos.x, 1, pos.y)) {
			Game::instance().getTileSystem().pathfinder->recalculateMap();
		}
	}
	oldKeyState = sf::Keyboard::isKeyPressed(sf::Keyboard::B);
}
