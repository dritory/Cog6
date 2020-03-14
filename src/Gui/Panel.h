#pragma once
#include <SFML/Graphics.hpp>
#include "GuiObject.h"
#include <vector>

class Panel : public GuiObject {

public:
	Panel();

	Panel(const sf::String &s, sf::Font& font, sf::Vector2f position);
	~Panel();

	bool update(sf::Event& e, sf::RenderWindow& window);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	virtual bool isMouseOverGUI();

private:

	std::vector <GuiObject> objects;
	sf::RectangleShape shape;

};