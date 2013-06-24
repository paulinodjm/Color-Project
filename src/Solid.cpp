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
	/*
  if (m_solid)
  {
    sf::Vector2i position = getPosition();
    sf::Vector2i move = m_speed;
    sf::IntRect bBox = getBbox();
    
    // horizontal move
    while (move.x > 0)
    {
      bBox.left++;
      if (tilemap.placeFree(bBox))
      {
        position.x++;
        move.x--;
      }
      else
      {
        bBox.left--;
        move.x = 0;
        hitWall();
      }
    }
    
    while (move.x < 0)
    {
      bBox.left--;
      if (tilemap.placeFree(bBox))
      {
        position.x--;
        move.x++;
      }
      else
      {
        bBox.left++;
        move.x = 0;
        hitWall();
      }
    }
    
    // vertical move
    while (move.y > 0)
    {
      bBox.top++;
      if (tilemap.placeFree(bBox))
      {
        position.y++;
        move.y--;
      }
      else
      {
        bBox.top++;
        move.y = 0;
        landed();
      }
    }
    
    while (move.y < 0)
    {
      bBox.top--;
      if (tilemap.placeFree(bBox))
      {
        position.y--;
        move.y++;
      }
      else
      {
        bBox.top--;
        move.y = 0;
        hitCeiling();
      }
    }
    
    setPosition(position);
  }
  else
  {
    setPosition(m_position.x + m_speed.x, m_position.y + m_speed.y);
  }
  //*/
  
  float deltaTime = m_clock.restart().asSeconds();
  sf::Vector2f speed = m_speed * deltaTime;
  setPosition(m_position.x + speed.x, m_position.y + speed.y);
}

