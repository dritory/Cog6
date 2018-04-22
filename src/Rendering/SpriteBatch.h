#pragma once
#include <SFML/Graphics.hpp>
#include "../GameObject.h"
#include <algorithm>

class GameObjectComparator
{
public:
	bool operator()(const GameObject* lhs, const GameObject* rhs) const;
};

class SpriteBatch : public sf::Drawable
{
public:
	SpriteBatch();

	void QueueObject(GameObject* object);
	void SetDirty() { m_Dirty = true; }
	void prepareDraw();
	long long getQueued() { return m_Queued; }

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void sort();
	
	std::vector<GameObject*> m_QueuedDraw;
	bool m_Dirty;
	long long m_Counter;
	long long m_Queued;
};
