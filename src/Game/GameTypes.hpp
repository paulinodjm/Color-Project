//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#pragma once

#include "../Engine/BaseTypes.hpp"
#include "../Engine/GameObject.hpp"
#include "../Engine/Tilemap.hpp"
#include <string>
#include "../Engine/Animation.hpp"
#include "../Engine/AnimatedSprite.hpp"
#include "../Engine/Camera.hpp"
#include "../Engine/SoundPlayer.hpp"

/*
///
/// MyObject
/// 
class MyObject : public e::Object, public e::Solid, public e::Drawable, public e::Camera
{
public:

  MyObject(e::Resources& resources);
  
  void calcView(sf::View& view) const;

protected:

  void init(e::Level& level);

  void update(float deltaTime);
  
  void draw(sf::RenderTarget& target, sf::RenderStates states) const;
  
  void moved();
  
private:

  bool m_move;
  e::AnimatedSprite m_sprite;
	sf::Clock m_clock;
	e::Tilemap *m_tilemap;
};


///
/// StaticObject
///
class StaticObject : public e::GameObject
{
public:

  StaticObject(e::Resources& resources);
  
  void update(float deltaTime);
  
  void touch(const Solid& solid);
  
  void untouch(const Solid& solid);
  
private:

  e::SoundBuffer m_soundBuffer; // FIXME segfault if the soundBuffer isn't keep here
  static e::SoundPlayer m_sound;
};

///
/// AutoFactory
///
template <typename T>
class AutoFactory : public e::ObjectFactory
{
public:
  
  e::Object* create()
  {
    return new T(getResources());
  }
};


///
/// object factories declaration
///
extern AutoFactory<MyObject>     moFactory;
extern AutoFactory<StaticObject> soFactory;
extern AutoFactory<e::Tilemap>   tmFactory;
//*/

