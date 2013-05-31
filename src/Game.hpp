//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#pragma once

#include <SFML/Graphics.hpp>
#include <set>
#include <map>
#include <string>

class Object;
class Drawable;
class ObjectFactory;

class Game
{
public:

  int mainLoop();
  
  
  void addObjectFactory(const std::string& name, ObjectFactory& factory);
  
  Object* createObject(const std::string& name);

protected:

  virtual bool loadRessources() {return true;}

  virtual void init() {}

  virtual bool update(float deltaTime) {return true;}

  virtual void finalize() {}

private:

  sf::RenderWindow      m_rendow;

  std::set<Object*>     m_objects;

  std::set<Drawable*>   m_drawables;
  
  std::map<std::string, ObjectFactory*> m_objectFactory;
};
