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
  
  Solid(const sf::IntRect& bounds, const sf::Vector2i& position = sf::Vector2i(0,0));
  
  /** set the bounds of the object, in relative coordinates */
  void setBounds(const sf::IntRect& bounds);
  
  /** return the bounds of the object, relative */
  const sf::IntRect& getBounds() const;
  
  /** return the bounding box of the object, in world coordinates */
  sf::IntRect getBbox() const;
  
  
  void setPosition(int x, int y);
  void setPosition(const sf::Vector2i& position);
  
  const sf::Vector2i& getPosition() const;
  
  
  void setSpeed(int x, int y);
  void setSpeed(const sf::Vector2i& speed);
  
  const sf::Vector2i& getSpeed() const;
  
  
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
  
  sf::Vector2i      m_position;
  
  sf::Vector2i      m_speed;
  
  sf::IntRect       m_bounds;
  
  std::set<Solid*>* m_touching;
  
  std::set<Solid*>* m_lastTouching;
  
friend class Game;
};

