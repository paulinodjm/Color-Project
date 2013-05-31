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
  
protected:

  virtual void touch(const Solid& other) {}
  
  virtual void untouch(const Solid& other) {}
  
  virtual void landed() {}
  
  virtual void fall() {}
  
  virtual void hitWall() {}
  
  virtual void hitCeiling() {}

private:

  void _touch(const Solid& other);
  
  void _untouch(const Solid& other);
  

  bool              m_solid;
  
  std::set<Solid*>  m_touching;
};

/**
* Object factory
*/
class ObjectFactory
{
public:

  virtual Object* create() = 0;
};
