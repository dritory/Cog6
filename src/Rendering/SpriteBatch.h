#pragma once
#include <SFML/Graphics.hpp>
#include "../GameObject.h"
#include <set>

struct GameObjectComparator
{
	bool operator()(const GameObject* lhs, const GameObject* rhs) const;
};

class SpriteBatch : public sf::Drawable
{
public:
	SpriteBatch();

	void QueueObject(GameObject* object);
	void SetDirty() { m_Dirty = true; }

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	std::set<GameObject*, GameObjectComparator> m_QueuedDraw;
	bool m_Dirty;
};
