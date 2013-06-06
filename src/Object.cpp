//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////

#include "Object.hpp"
#include <iostream>

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

Solid::Solid(const sf::IntRect& bounds, const sf::Vector2i& position) : m_bounds(bounds), m_position(position), m_solid(true) {}

void Solid::setBounds(const sf::IntRect& bounds)
{
  m_bounds = bounds;
}

const sf::IntRect& Solid::getBounds() const
{
  return m_bounds;
}

sf::IntRect Solid::getBbox() const
{
  sf::IntRect bBox = m_bounds;
  bBox.top += m_position.y;
  bBox.left += m_position.x;
  return bBox;
}

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

void Solid::setSolid(bool solid)
{
  m_solid = solid;
}

bool Solid::isSolid() const
{
  return m_solid;
}

void Solid::collideWith(const Solid& solid)
{
  //std::cout << "collision" << std::endl;
}
