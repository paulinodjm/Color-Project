//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#pragma once

#include <SFML/Graphics.hpp>
#include "BaseTypes.hpp"
#include <map>
#include <vector>
#include <string>
#include "Solid.hpp"
#include "Drawable.hpp"
#include "Object.hpp"
#include "Camera.hpp"

class Level : public Drawable
{
public:

  Level();
  
  virtual ~Level();
  
  
  void addObject(Object* object);
  
  /** return the first Object identified by this name */
  Object* getObject(const std::string& name);
  
  /** return all the objects identified by this name */
  std::vector<Object*> getObjects(const std::string& name);
  
  void deleteObjects();
  
  
  void init();
  
  void update();
  
  void performCollisions();
  
  void draw(sf::RenderTarget& target, sf::RenderStates states) const;
  
  
  void setPaused(bool paused);
  
  bool isPaused() const;
  
  
  Camera* getCamera() const;
  
  void setCamera(Camera* camera);
  
  
private:

  bool m_paused;

  std::multimap<std::string, Object*>   m_objects;

  std::multimap<int, Drawable*>         m_drawables;
  
  std::vector<Solid*>                   m_solids;

  Camera*                               m_camera;
};
