//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#pragma once

#include <vector>
#include <set>
#include <SFML/Graphics.hpp>
#include "BaseTypes.hpp"

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
  
  virtual void setPosition(int x, int y);
  virtual void setPosition(const sf::Vector2i& position);
  
  const sf::Vector2i& getPosition() const;
  
  void setSolid(bool solid);
  
  bool isSolid() const;
  
  const std::set<Solid*>& getTouchingSolids() const;
  
protected:

  virtual void touch(const Solid& other) {}
  
  virtual void untouch(const Solid& other) {}
  
  virtual void landed() {}
  
  virtual void fall() {}
  
  virtual void hitWall() {}
  
  virtual void hitCeiling() {}

private:

  void collideWith(Solid& other);
  
  void endCollision();
  
  void invertCollisionBuffers();
  

  bool              m_solid;
  
  sf::Vector2i      m_position;
  
  sf::IntRect       m_bounds;
  
  std::set<Solid*>* m_touching;
  
  std::set<Solid*>* m_lastTouching;
  
friend class Game;
};

