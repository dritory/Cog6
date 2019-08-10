#pragma once
#include <SFML\Graphics.hpp>
class Gui
{
public:
	Gui();
	~Gui();



	void initialize();

	virtual void update(sf::Event& e, sf::RenderWindow& window);

	virtual void draw(sf::RenderTarget& target);

	

private:


};

