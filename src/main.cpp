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
#include <string>
#include <SFML/Graphics.hpp>

class MyObject : public GameObject
{
public:

  MyObject(Resources& resources) : GameObject(resources)
  {
    setSprite(*resources.getSprite("sprite"));
    setBounds(sf::FloatRect(0,0,32,32));
  }

protected:

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
  }
  
  void landed() 
  {
    std::cout << "on ground!" << std::endl;
  }
  
  void hitWall() 
  {
    std::cout << "hit a wall" << std::endl;
  }
  
  void hitCeiling() 
  {
    std::cout << "hit the ceiling!" << std::endl;
  }
  
private:

	sf::Clock m_clock;
};

class StaticObject : public GameObject
{
public:

  StaticObject(Resources& resources) : GameObject(resources)
  {
    setSprite(*resources.getSprite("white"));
    setBounds(sf::FloatRect(0,0,32,32));
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

  game.addObjectFactory("MyObject", moFactory);
  game.addObjectFactory("StaticObject", soFactory);
  
  // resources loading and distribution
  sf::Texture* texture = game.getTextureLoader().get("data/tileset.png");
 
  moFactory.getResources().addSprite("sprite", sf::Sprite(*texture, sf::IntRect(0, 128, 32, 32)));
  soFactory.getResources().addSprite("white", sf::Sprite(*texture, sf::IntRect(64, 0, 32, 32)));
  soFactory.getResources().addSprite("red", sf::Sprite(*texture, sf::IntRect(32, 0, 32, 32)));
  
  // tilemap loading
  game.loadTilemap("data/tilemap.json");
  game.loadObjects("data/objects.json");
  
  // main loop
  return game.mainLoop();
}//*/

