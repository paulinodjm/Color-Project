//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////

#include "Solid.hpp"
#include <iostream>

Solid::Solid() : Solid(sf::IntRect()) {}

Solid::Solid(const sf::IntRect& bounds, const sf::Vector2i& position) : m_bounds(bounds), m_position(position), m_solid(true) 
{
  m_touching = new std::set<Solid*>();
  m_lastTouching = new std::set<Solid*>();
}

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

void Solid::collideWith(Solid& solid)
{
  m_touching->insert(&solid);
  // first touch
  auto it = m_lastTouching->find(&solid);
  if (it == m_lastTouching->end())
  {
    touch(solid);
  }
  else
  {
    m_lastTouching->erase(it);
  }
}

/** invert the two collisions buffers */
void Solid::endCollision()
{
  for (auto it = m_lastTouching->begin(); it!=m_lastTouching->end(); it++)
  {
    (*it)->untouch(*this);
  }

  invertCollisionBuffers();
}

void Solid::invertCollisionBuffers()
{
  std::set<Solid*>* tmp = m_lastTouching;
  tmp->clear();
  m_lastTouching = m_touching;
  m_touching = tmp;
}

#include "Solid.hpp"


