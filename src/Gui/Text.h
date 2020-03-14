#pragma once
#include <SFML/Graphics.hpp>
#include "GuiObject.h"
class Text : public GuiObject {

public:
	Text(const sf::String &s,const sf::Font &font, const sf::Vector2f &pos);

	Text(const sf::String &s, const sf::Font &font, sf::Vector2f position, bool sentered);
	~Text();

	 bool update(sf::Event& e, sf::RenderWindow& window);

	 void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	 void setString(const sf::String &s) {
		 text.setString(s);
	 }
private:

	sf::Text text;
};