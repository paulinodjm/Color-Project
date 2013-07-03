//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#pragma once

#include <vector>
#include <set>
#include <SFML/Graphics.hpp>
#include "BaseTypes.hpp"
#include "Tilemap.hpp"
#include <iostream>

/**
* Base class for each object that can collide with others and with
* the map.
*/
class Solid
{
public:

  Solid();
  
  Solid(const sf::FloatRect& bounds, const sf::Vector2f& position = sf::Vector2f(0,0));
  
  /** set the bounds of the object, in relative coordinates */
  void setBounds(const sf::FloatRect& bounds);
  
  /** return the bounds of the object, relative */
  const sf::FloatRect& getBounds() const;
  
  /** return the bounding box of the object, in world coordinates */
  sf::FloatRect getBbox() const;
  sf::FloatRect getBbox(float xOffset, float yOffset) const;
  sf::FloatRect getBbox(const sf::Vector2f& offset) const;
  
  
  void setPosition(float x, float y);
  void setPosition(const sf::Vector2f& position);
  
  const sf::Vector2f& getPosition() const;
  
  
  void setSpeed(float x, float y);
  void setSpeed(const sf::Vector2f& speed);
  
  const sf::Vector2f& getSpeed() const;
  
  
  void setSolid(bool solid);
  
  bool isSolid() const;
  
  const std::set<Solid*>& getTouchingSolids() const;
  
  
  void move(const Tilemap& tilemap);
  
protected:

  virtual void moved() {}

  virtual void touch(const Solid& other) {}
  
  virtual void untouch(const Solid& other) {}
  
  virtual void landed() {}
  
  virtual void fall() {} // Dont work
  
  virtual void hitWall() {}
  
  virtual void hitCeiling() {}

private:

  void collideWith(Solid& other);
  
  void endCollision();
  
  void invertCollisionBuffers();
  

  bool              m_solid;
  
  sf::Vector2f      m_position;
  
  sf::Vector2f      m_speed;
  
  sf::FloatRect     m_bounds;
  
  std::set<Solid*>* m_touching;
  
  std::set<Solid*>* m_lastTouching;
  
  sf::Clock					m_clock;
  
friend class Level;
};

