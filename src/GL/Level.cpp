#include "Level.h"



Level::Level() {
	this->game = Game::Instance();
}



Level::~Level() {

	this->game = nullptr;
}
