//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////

#include <iostream>
#include "BaseTypes.hpp"
#include "Game.hpp"
#include "GameObject.hpp"
#include "TextureLoader.hpp"
#include <string>
#include <SFML/Graphics.hpp>

class MyObject : public GameObject
{
public:

  MyObject() : GameObject()
  {
    setSprite(*getResources()->getSprite("sprite"));
    setBounds(sf::IntRect(0,0,32,32));
    setPosition(50, 50);
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
    
    sf::Vector2i position = getPosition();
    position.x += (right - left);
    position.y += (down - up);
    setPosition(position);
  }

  void touch(const Solid& solid)
  {
    std::cout << "touch " << (&solid) << std::endl;
  }
  
  void untouch(const Solid& solid)
  {
    std::cout << "untouch " << (&solid) << std::endl;
  }
};

class StaticObject : public GameObject
{
public:

  StaticObject() : GameObject()
  {
    setSprite(*getResources()->getSprite("sprite"));
    setBounds(sf::IntRect(0,0,32,32));
  }
};

template <typename T>
class AutoFactory : public ObjectFactory
{
public:

  AutoFactory() 
  { 
    T::setResources(getResources());
  }
  
  Object* create()
  {
    return new T();
  }
};

/************************************
* main                              *
************************************/
int main(int argc, char** argv)
{			
  // object factories declaration
  AutoFactory<MyObject> moFactory;
  AutoFactory<StaticObject> soFactory;
  
  // resources loading and distribution
  TextureLoader loader;
  sf::Texture* texture = loader.get("data/tileset.png");
  sf::Sprite sprite(*texture, sf::IntRect(0,0,32,32));
  
  moFactory.getResources().addSprite("sprite", sprite);
  soFactory.getResources().addSprite("sprite", sprite);

  // game initialisation
  Game game;
  game.addObjectFactory("myObject", moFactory);
  game.addObjectFactory("staticObject", soFactory);
  
  // object creation
  game.createObject("myObject"); 
  game.createObject("staticObject");
  GameObject* go = (GameObject*)game.createObject("staticObject");
  go->setPosition(100,100);
  go = (GameObject*)game.createObject("staticObject");
  go->setPosition(32,0);
  
  // main loop
  return game.mainLoop();
}
