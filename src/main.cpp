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

class MyObject : public GameObject
{
public:

  MyObject(Resources& resources) : GameObject(resources), m_tilemap(nullptr)
  {
    setSprite(*resources.getSprite("sprite"));
    setBounds(sf::FloatRect(1,0,30,32));
  }

protected:

  void init(Level& level)
  {
    m_tilemap = dynamic_cast<Tilemap*>( level.getObject("tilemap") );
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
    
    setSpeed( (right-left)*120, (down-up)*120 );
    if (m_tilemap)
      move(*m_tilemap);
  }
  
private:

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
  }
  
  void update(float deltaTime)
  {
  }
  
  void touch(const Solid& solid)
  {
    setSprite(*(getResources()->getSprite("red")));
  }
  
  void untouch(const Solid& solid)
  {
    setSprite(*(getResources()->getSprite("white")));
  }
};

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
  
  // main loop
  return game.mainLoop();
}//*/

