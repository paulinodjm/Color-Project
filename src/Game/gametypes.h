//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#pragma once

#include "../Engine/object.h"
#include "../Engine/solid.h"
#include "../Engine/camera.h"
#include "../Engine/actor.h"
#include "../Engine/level.h"
#include "../Engine/animatedsprite.h"
#include "../Engine/staticsprite.h"
#include "../Engine/contentmanager.h"

////////////////////////////////////////////////////////////////////////
class PLAYER : public OBJECT, public ACTOR, public SOLID, public CAMERA
{
public:

  PLAYER();
  
  /// Implements OBJECT
  bool Load(CONTENTMANAGER& contentManager);
  void Init(LEVEL& level);
  
  /// Implements ACTOR
  void Update();
  
  /// Implements SOLID
  void Moved();
  void Touch(const SOLID& other);
  void Untouch(const SOLID& other);
  
  /// Implements CAMERA
  void CalcView(sf::View& view) const;
  
private:

  ANIMATEDSPRITE sprite;
};

////////////////////////////////////////////////
class STATICOBJECT : public OBJECT, public SOLID
{
public:

  STATICOBJECT();
  
  /// Implements OBJECT
  bool Load(CONTENTMANAGER& contentManager);
  void Init(LEVEL& level);
  
  /// Implements SOLID
  void Moved();
  void Touch(const SOLID& other);
  void Untouch(const SOLID& other);
  
private:

  ANIMATEDSPRITE                      sprite;
  static std::shared_ptr<SOUNDBUFFER> soundbuffer;
  static SOUND                        sound;
};

