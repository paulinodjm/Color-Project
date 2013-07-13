//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////

#include <iostream>
#include "BaseTypes.hpp"
#include "Game.hpp"
#include "GameObject.hpp"
#include "TextureLoader.hpp"
#include "Tileset.hpp"
#include "Tilemap.hpp"
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Animation.hpp"
#include "AnimatedSprite.hpp"
#include "Camera.hpp"

class MyObject : public Object, public Solid, public Drawable, public Camera
{
public:

  MyObject(Resources& resources) : Object(resources), Solid(), Drawable(),
    m_tilemap(nullptr), m_move(false)
  {
    m_sprite.setAnimation(*getResources()->getAnimation("idle"));
    m_sprite.setFrameTime(sf::seconds(0.15f));
    m_sprite.setOrigin(16,0);
    setBounds(sf::FloatRect(2,0,28,32));
  }
  
  void calcView(sf::View& view) const
  {
    view.setCenter(getPosition());
  }

protected:

  void init(Level& level)
  {
    m_tilemap = dynamic_cast<Tilemap*>( level.getObject("tilemap") );
    level.setCamera(this);
  }

  void update(float deltaTime)
  {
    bool up = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z);
    bool down = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S);
    bool left = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q);
    bool right = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D);
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::C))
      setSolid(true);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::V))
      setSolid(false);
    
    setSpeed( (right-left)*200, (down-up)*200 );
    sf::Vector2f oldPos = getPosition();
    if (m_tilemap)
      move(*m_tilemap);
    
    if (oldPos != getPosition())
    {
      if (!m_move)
      {
        m_sprite.setAnimation(*getResources()->getAnimation("walk"));
        m_move = true;
      }
      
      if (getPosition().x < oldPos.x)
      {
        m_sprite.setScale(-1, 1);
      }
      else if (getPosition().x > oldPos.x)
      {
        m_sprite.setScale(1, 1);
      }
    }
    else
    {
      if (m_move)
      {
        m_sprite.setAnimation(*getResources()->getAnimation("idle"));
        m_move = false;
      }
    }
    
    m_sprite.update(m_clock.restart());
  }
  
  void draw(sf::RenderTarget& target, sf::RenderStates states) const
  {
    target.draw(m_sprite);
  }
  
  void moved()
  {
    m_sprite.setPosition(getPosition().x + 16, getPosition().y);
  }
  
private:

  bool m_move;
  AnimatedSprite m_sprite;
	sf::Clock m_clock;
	Tilemap *m_tilemap;
};

class StaticObject : public GameObject
{
public:

  StaticObject(Resources& resources) : GameObject(resources)
  {
    setSprite(*resources.getSprite("white"));
    setBounds(sf::FloatRect(0,0,32,32));
    m_sound.setBuffer(*getResources()->getSoundBuffer("sound"));
  }
  
  void update(float deltaTime)
  {
  }
  
  void touch(const Solid& solid)
  {
    setSprite(*(getResources()->getSprite("red")));
    m_sound.play();
  }
  
  void untouch(const Solid& solid)
  {
    setSprite(*(getResources()->getSprite("white")));
  }
  
private:

  static sf::Sound m_sound;
};
sf::Sound StaticObject::m_sound;

template <typename T>
class AutoFactory : public ObjectFactory
{
public:
  
  Object* create()
  {
    return new T(getResources());
  }
};

/************************************
* main                              *
************************************/
int main(int argc, char** argv)
{			
  Game game;

  // object factories declaration
  AutoFactory<MyObject>     moFactory;
  AutoFactory<StaticObject> soFactory;
  AutoFactory<Tilemap>      tmFactory;

  game.addObjectFactory("MyObject", moFactory);
  game.addObjectFactory("StaticObject", soFactory);
  game.addObjectFactory("Tilemap", tmFactory);
  
  // sound test
  soFactory.getResources().addSoundBuffer("sound", game.getSoundLoader().get("data/sound.wav"));
  
  // main loop
  return game.mainLoop();
}//*/

