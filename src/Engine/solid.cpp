//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#include "solid.h"

SOLID::SOLID() : SOLID(sf::FloatRect()) {}

SOLID::SOLID(const sf::FloatRect& bounds_, const sf::Vector2f& position_) 
: 
  bounds(bounds_), 
  position(position_), 
  isSolid(true)
{
  touching = new std::set<SOLID*>();
  lastTouching = new std::set<SOLID*>();
}

void SOLID::SetBounds(const sf::FloatRect& value)
{
  bounds = value;
}

const sf::FloatRect& SOLID::Bounds() const
{
  return bounds;
}

sf::FloatRect SOLID::Bbox() const
{
  sf::FloatRect bBox = bounds;
  bBox.top += position.y;
  bBox.left += position.x;
  return bBox;
}

sf::FloatRect SOLID::Bbox(float xOffset, float yOffset) const
{
  sf::FloatRect bBox = Bbox();
  bBox.left += xOffset;
  bBox.top += yOffset;
  return bBox;
}

sf::FloatRect SOLID::Bbox(const sf::Vector2f& offset) const
{
  return Bbox(offset.x, offset.y);
}

const sf::Vector2f& SOLID::Position() const
{
  return position;
}

void SOLID::SetPosition(float x, float y)
{
  position = sf::Vector2f(x, y);
  Moved();
}

void SOLID::SetPosition(const sf::Vector2f& pos)
{
  position = pos;
  Moved();
}

void SOLID::SetSpeed(float x, float y)
{
  SetSpeed(sf::Vector2f(x, y));
}

void SOLID::SetSpeed(const sf::Vector2f& speed_)
{
  speed = speed_;
}
  
const sf::Vector2f& SOLID::Speed() const
{
  return speed;
}

void SOLID::SetSolid(bool solid_)
{
  isSolid = solid_;
}

bool SOLID::Solid() const
{
  return isSolid;
}

void SOLID::CollideWith(SOLID& solid)
{
  touching->insert(&solid);
  // first touch
  auto it = lastTouching->find(&solid);
  if (it == lastTouching->end())
  {
    Touch(solid);
  }
  else
  {
    lastTouching->erase(it);
  }
}

void SOLID::EndCollision()
{
  for (auto it = lastTouching->begin(); it!=lastTouching->end(); it++)
  {
    (*it)->Untouch(*this);
  }

  InvertCollisionBuffers();
}

void SOLID::InvertCollisionBuffers()
{
  std::set<SOLID*>* tmp = lastTouching;
  tmp->clear();
  lastTouching = touching;
  touching = tmp;
}

const std::set<SOLID*>& SOLID::TouchingSolids() const
{
  return *lastTouching;
}

/*
void SOLID::Move(const Tilemap& tilemap)
{
  sf::Vector2f speed = m_speed * m_clock.restart().asSeconds();
  int tileSize = tilemap.getTileSize();
  sf::FloatRect bBox;
  
  if (m_solid)
  {
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
        hitWall();
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
          m_position.y = bBox.top - m_bounds.top;
          hitCeiling();
        }
        else
        {
          float bottom = (int)(bBox.top + bBox.height)/tileSize*tileSize;
          bBox.top = bottom - bBox.height;
          m_position.y = bBox.top - m_bounds.top;
          landed();
        }
      }
    }
  }
  else
  {
    m_position += speed;
  }
  
  moved();
}//*/

