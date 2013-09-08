//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <vector>
#include <map>
#include <string>
#include <memory>
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
  
  bool Load(
    const std::string& filename,
    CONTENTMANAGER& contentManager,
    const std::map<std::string, OBJECTFACTORY*>& factories);  
  bool PerformLoading(CONTENTMANAGER& contentManager);
  void Init();
  bool Update();
  void PerformMove();
  void PerformCollisions();
  
  bool Paused() const;
  void SetPaused(bool pause);
  
  bool AddSprite(STATICSPRITE& sprite, int depth=0);
  bool AddSprite(ANIMATEDSPRITE& sprite, int depth=0);
  bool AddObject(OBJECT* obj, const std::string& name="", int depth=0);
  
  OBJECT* Object(const std::string& name) const;
  std::vector<OBJECT*> Objects(const std::string& name) const;
  void DeleteObjects();
  
  CAMERA* Camera() const;
  void SetCamera(CAMERA* camera);
  
  const std::shared_ptr<TILEMAP>& Tilemap() const;
  void SetTilemap(const std::shared_ptr<TILEMAP>& tilemap);
  
protected:

  void draw(sf::RenderTarget& target, sf::RenderStates states) const;
  
private:

  bool                                paused;
  std::multimap<std::string, OBJECT*> objects;
  std::vector<ACTOR*>                 actors;
  std::multimap<int, DRAWABLE*>       drawables;
  std::vector<SOLID*>                 solids;
  CAMERA*                             camera;
  std::shared_ptr<TILEMAP>            tilemap;
};

