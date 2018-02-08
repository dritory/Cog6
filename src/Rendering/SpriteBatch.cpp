#include "SpriteBatch.h"
#include "../EntitySystem/Entity.h"

bool GameObjectComparator::operator()(const GameObject* lhs, const GameObject* rhs) const
{
	auto& lp = lhs->m_Position;
	auto& rp = rhs->m_Position;

	if ((int)lp.y != (int)rp.y) return (int)lp.y < (int)rp.y;

	auto a = (lp.x / 4.0f + lp.y + lp.z / 4.0f);
	auto b = (rp.x / 4.0f + rp.y + rp.z / 4.0f);
	if (a != b) return a < b;
	return lhs->m_Id < rhs->m_Id;
}

SpriteBatch::SpriteBatch()
{
}

void SpriteBatch::QueueObject(GameObject* object)
{
	if (m_Dirty)
	{
		m_QueuedDraw.clear();
		m_Dirty = false;
	}

	auto pos = object->GetPosition();
	auto a = (pos.x / 4.0f + pos.y + pos.z / 4.0f);
	auto b = (pos.x / 2.0f - pos.z / 2.0f);
	if (a < -64 || a >= 1200 + 64 || b < -64 || b >= 1600 + 64) return;

	m_QueuedDraw.insert(object);
}

void SpriteBatch::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for(auto it : m_QueuedDraw)
	{
		target.draw(*it);
	}
}

