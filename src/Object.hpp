//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////

#pragma once

#include <SFML/Graphics.hpp>
#include <set>
#include "BaseTypes.hpp"
#include "Resources.hpp"

/**
* Base class for each object in the game.
*/
class Object
{
public:

  Object();
  
  Object(Resources& resources);

  Resources* getResources();
  
  void setResources(Resources& resources);

protected:

  virtual void init() {}

  virtual void update(float deltaTime) {}

private:

  Resources* m_resources;

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
* Object factory
*/
class ObjectFactory
{
public:

  virtual Object* create() = 0;
  
  Resources&  getResources();
  
private:

  Resources m_resources;
};//*/
