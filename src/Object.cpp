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

const sf::Vector2i& Solid::getPosition() const
{
  return m_position;
}

void Solid::setPosition(int x, int y)
{
  m_position = sf::Vector2i(x, y);
}

void Solid::setPosition(const sf::Vector2i& position)
{
  m_position = position;
}

void Solid::collideWith(const Solid& solid)
{
}
