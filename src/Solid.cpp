//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////

#include "Solid.hpp"
#include <iostream>

Solid::Solid() : Solid(sf::FloatRect()) {}

Solid::Solid(const sf::FloatRect& bounds, const sf::Vector2f& position) 
: 
  m_bounds(bounds), 
  m_position(position), 
  m_solid(true)
{
  m_touching = new std::set<Solid*>();
  m_lastTouching = new std::set<Solid*>();
}

void Solid::setBounds(const sf::FloatRect& bounds)
{
  m_bounds = bounds;
}

const sf::FloatRect& Solid::getBounds() const
{
  return m_bounds;
}

sf::FloatRect Solid::getBbox() const
{
  sf::FloatRect bBox = m_bounds;
  bBox.top += m_position.y;
  bBox.left += m_position.x;
  return bBox;
}

sf::FloatRect Solid::getBbox(float xOffset, float yOffset) const
{
  sf::FloatRect bBox = getBbox();
  bBox.left += xOffset;
  bBox.top += yOffset;
  return bBox;
}

sf::FloatRect Solid::getBbox(const sf::Vector2f& offset) const
{
  return getBbox(offset.x, offset.y);
}

const sf::Vector2f& Solid::getPosition() const
{
  return m_position;
}

void Solid::setPosition(float x, float y)
{
  m_position = sf::Vector2f(x, y);
  moved();
}

void Solid::setPosition(const sf::Vector2f& position)
{
  m_position = position;
  moved();
}

void Solid::setSpeed(float x, float y)
{
  setSpeed(sf::Vector2f(x, y));
}

void Solid::setSpeed(const sf::Vector2f& speed)
{
  m_speed = speed;
}
  
const sf::Vector2f& Solid::getSpeed() const
{
  return m_speed;
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

const std::set<Solid*>& Solid::getTouchingSolids() const
{
  return *m_lastTouching;
}

void Solid::move(const Tilemap& tilemap)
{
  sf::Vector2f speed = m_speed * m_clock.restart().asSeconds();
  unsigned int tileSize = tilemap.getTileSize();
  sf::FloatRect bBox;
  
  // horizontal move
  if (speed.x != 0.f)
  {
    m_position.x += speed.x;
    bBox = getBbox();
    if ( !tilemap.placeFree(bBox) )
    {
      if (speed.x < 0)
      {
        bBox.left = (int)(bBox.left)/tileSize*tileSize + tileSize;
      }
      else
      {
        float right = (int)(bBox.left + bBox.width)/tileSize*tileSize;
        bBox.left = right - bBox.width;
      }
      m_position.x = bBox.left - m_bounds.left;
    }
  }
  
  // vertical move
  if (speed.y != 0.f)
  {
    m_position.y += speed.y;
    bBox = getBbox();
    if ( !tilemap.placeFree(bBox) )
    {
      if (speed.y < 0)
      {
        bBox.top = (int)(bBox.top)/tileSize*tileSize + tileSize;
      }
      else
      {
        float bottom = (int)(bBox.top + bBox.height)/tileSize*tileSize;
        bBox.top = bottom - bBox.height;
      }
      m_position.y = bBox.top - m_bounds.top;
    }
  }
  
  moved();
}

