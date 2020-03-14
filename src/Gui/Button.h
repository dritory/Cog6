#pragma once
#include <SFML/Graphics.hpp>
#include "GuiObject.h"
#include <functional>
#include <memory>

class Button : public GuiObject {

public:
	typedef std::function<void()> Callback;

	Button();

	Button(const sf::String &s, sf::Font& font, sf::Vector2f position);
	~Button();

	bool update(sf::Event& e, sf::RenderWindow& window);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void setCallback(Callback callback);

	void setString(const sf::String &s) {
		text.setString(s);
	}

private:

	sf::Color bgNormal;
	sf::Color bgHover;
	sf::Color bgClicked;
	sf::Color textNormal;
	sf::Color textHover;
	sf::Color textClicked;
	sf::Color border;

	float borderThickness;
	float borderRadius;
	sf::Uint32 style;

	sf::RectangleShape button;
	sf::Font font;
	unsigned int fontSize;
	sf::Text text;

	Callback callback;
	bool oldHidden;



};