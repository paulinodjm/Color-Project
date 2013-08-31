//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <vector>
#include <map>
#include <string>
#include "staticsprite.h"
#include "animatedsprite.h"
#include "contentmanager.h"
#include "object.h"
#include "solid.h"
#include "drawable.h"
#include "actor.h"
#include "camera.h"
#include "objectfactory.h"
#include "tilemap.h"

class LEVEL : public sf::Drawable
{
public:

  LEVEL();
  virtual ~LEVEL();
  
  // temporary Save() definition
  bool Load(
    const std::string& filename, 
    std::map<std::string, OBJECTFACTORY*>& factories, 
    CONTENTMANAGER& contentManager
  );  
  bool Save(std::string& filename) const;
  
  bool Paused() const;
  void SetPaused(bool pause);
  
  bool AddSprite(STATICSPRITE& sprite, int depth=0);
  bool AddSprite(ANIMATEDSPRITE& sprite, int depth=0);
  // for tests
  bool AddObject(OBJECT* obj, const std::string& name="", int depth=0);
  
  OBJECT* Object(const std::string& name) const;
  std::vector<OBJECT*> Objects(const std::string& name) const;
  void DeleteObjects();
  
  CAMERA* Camera() const;
  void SetCamera(CAMERA* camera);
  
  TILEMAP& Tilemap();
  
  void Init();
  bool Update();
  void PerformMove();
  void PerformCollisions();
  
protected:

  void draw(sf::RenderTarget& target, sf::RenderStates states) const;
  
private:

  bool                                paused;
  std::multimap<std::string, OBJECT*> objects;
  std::vector<ACTOR*>                 actors;
  std::multimap<int, DRAWABLE*>       drawables;
  std::vector<SOLID*>                 solids;
  CAMERA*                             camera;
  TILEMAP                             tilemap;
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
