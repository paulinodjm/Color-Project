//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////

#pragma once

#include <SFML/Graphics.hpp>
#include <set>
#include "Game.hpp"

/**
* Base class for each object in the game.
*/
class Object
{
protected:

  virtual void init() {}

  virtual void update(float deltaTime) {}

friend class Game;
};

/**
* Base class for each visible object.
*/
class Drawable : public sf::Drawable
{
public:

  Drawable();

  void setVisible(bool visible);

  bool isVisible() const;

private:

  bool m_visible;
};

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
  
protected:

  virtual void touch(const Solid& other) {}
  
  virtual void untouch(const Solid& other) {}
  
  virtual void landed() {}
  
  virtual void fall() {}
  
  virtual void hitWall() {}
  
  virtual void hitCeiling() {}

private:

  void collideWith(const Solid& other);
  

  bool              m_solid;
  
  std::set<Solid*>  m_touching;
  
  sf::Vector2i      m_position;
  
  sf::IntRect       m_bounds;
  
friend class Game;
};


/**
* Object factory
*/
class ObjectFactory
{
public:

  virtual Object* create() = 0;
};
