#pragma once
#include <SFML/Graphics.hpp>

enum State {
	NORMAL,
	HOVER,
	CLICKED,
};
class GuiObject : public sf::Drawable, protected sf::Transformable {
	 
public:
	GuiObject();

	GuiObject(sf::Vector2f position);
	~GuiObject();

	virtual void update(sf::Event& e, sf::RenderWindow& window);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	int getState();

	virtual void SetPosition(const sf::Vector2f& position);
	const sf::Vector2f& GetPosition() { return position; }

	void setHidden(bool hidden) { this->hidden = hidden; }
	bool isHidden() { return hidden; }

	bool inBounds(const sf::Vector2f& position);
	bool inBounds(int x, int y);
	bool inBounds(float x, float y);
	bool inBounds(const sf::Vector2i& position);


protected:

	sf::Vector2f position;
	sf::Vector2f size;

	bool sentered;

	bool hidden = false;

	bool hover;

	bool pressed;

	int state;

};