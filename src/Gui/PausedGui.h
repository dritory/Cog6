#pragma once
#include "Gui.h"

class PausedGui : Gui
{
public:
	PausedGui();
	~PausedGui();

	void initialize();

	void update(sf::Event& e, sf::RenderWindow& window);

	void draw(sf::RenderTarget& target);


private:

	sf::Text text;
	sf::Text text1;
	sf::Text text2;
	sf::Text text3;
};