#include "GameObject.h"

unsigned int GameObject::g_Id = 0;

GameObject::GameObject()
{
	m_Id = g_Id++;
}

void GameObject::SetPosition(const sf::Vector3f& position)
{
	m_Position = position;
	setPosition(m_Position.x / 2.0f - m_Position.z / 2.0f, m_Position.x / 4.0f - m_Position.y / 2.0f + m_Position.z / 4.0f);
}

void GameObject::pushState(ObjectState & state)
{
	if ( state.id == m_Id ) {
		SetPosition(sf::Vector3f(state.x, state.y, state.z));
	}
}
