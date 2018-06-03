#include "SpriteBatch.h"
#include "../EntitySystem/Entity.h"

bool GameObjectComparator::operator()(const GameObject* lhs, const GameObject* rhs) const
{
	auto& lp = lhs->m_Position;
	auto& rp = rhs->m_Position;

	auto a = (lp.x / 4.0f + lp.y / 2.0f + lp.z / 4.0f);
	auto b = (rp.x / 4.0f + rp.y / 2.0f + rp.z / 4.0f);
	if (a != b) return a < b;
	return lhs->m_Id > rhs->m_Id;
}

SpriteBatch::SpriteBatch() : m_Counter()
{
	m_QueuedDraw.resize(256);
}

void SpriteBatch::QueueObject(GameObject* object)
{
	if (m_Dirty)
	{
		m_Queued = m_Counter;
		//m_QueuedDraw.clear();
		m_Counter = 0;
		m_Dirty = false;
	}

	auto pos = object->GetPosition();
	auto a = (pos.x / 4.0f + pos.y + pos.z / 4.0f);
	auto b = (pos.x / 2.0f - pos.z / 2.0f);
	//if (a < -64 || a >= 1200 + 64 || b < -64 || b >= 1600 + 64) return;
	if (m_Counter + 1 > (int)m_QueuedDraw.size())
		m_QueuedDraw.resize(m_QueuedDraw.size() * 2);
	m_QueuedDraw[m_Counter] = object;
	m_Counter++;
}

void SpriteBatch::prepareDraw()
{
	std::sort(m_QueuedDraw.begin(), m_QueuedDraw.begin() + m_Counter, GameObjectComparator());
}

void SpriteBatch::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (int i = 0; i < m_Counter; ++i)
	{
		target.draw(*m_QueuedDraw[i]);
	}
}


