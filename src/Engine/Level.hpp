//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#pragma once

#include "drawable.h"
#include <SFML/Graphics/Drawable.hpp>

class LEVEL : public sf::Drawable
{
  LEVEL();
  ~LEVEL();
};

/*
namespace e
{
  class Level// : public Drawable
  {
  /*
  public:

    Level();
    
    virtual ~Level();
    
    
    void addObject(Object* object);
    
    Object* getObject(const std::string& name);
    
    std::vector<Object*> getObjects(const std::string& name);
    
    void deleteObjects();
    
    
    void init();
    
    bool update();
    
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
}//*/
