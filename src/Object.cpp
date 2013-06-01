//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////

#include "Object.hpp"

Drawable::Drawable() : sf::Drawable(), m_visible(true) {}

void Drawable::setVisible(bool visible)
{
  m_visible = visible;
}

bool Drawable::isVisible() const
{
  return m_visible;
}


Solid::Solid() : m_solid(true) {}

void Solid::setPosition(int x, int y)
{}

void Solid::setPosition(const sf::Vector2i& position)
{}

void Solid::collideWith(const Solid& solid)
{
}


GameObject::GameObject() : Drawable(), Solid() {}

void GameObject::setPosition(int x, int y)
{
  Solid::setPosition(x, y);
}

void GameObject::setPosition(const sf::Vector2i& position)
{
  setPosition(position.x, position.y);
}
