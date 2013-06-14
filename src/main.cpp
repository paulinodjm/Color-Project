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

  StaticObject(Resources& resources) : GameObject(resources)
  {
    setSprite(*resources.getSprite("sprite"));
    setBounds(sf::IntRect(0,0,32,32));
  }
};

class Tilemap : public GameObject
{
public:
  Tilemap(Resources& resources) : GameObject(resources)
  {
    setSolid(false);
    setSprite(*resources.getSprite("tileset"));
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
  // object factories declaration
  AutoFactory<MyObject>     moFactory;
  AutoFactory<StaticObject> soFactory;
  AutoFactory<Tilemap>      tFactory;
  
  // resources loading and distribution
  TextureLoader loader;
  sf::Texture* texture = loader.get("data/tileset.png");
  sf::Sprite sprite(*texture, sf::IntRect(0,0,32,32));
  
  moFactory.getResources().addSprite("sprite", sprite);
  soFactory.getResources().addSprite("sprite", sprite);
  
  std::cout << "Game initialisation" << std::endl;
  
  // game initialisation
  Game game;
  game.addObjectFactory("myObject", moFactory);
  game.addObjectFactory("staticObject", soFactory);
  game.addObjectFactory("tilemap", tFactory);
  
  std::cout << "Objects creation" << std::endl;
  
  // object creation
  game.createObject("myObject");
  game.createObject("staticObject");
  /*GameObject* go = (GameObject*)game.createObject("tilemap");
  go->setPosition(200,0);*/
  
  std::cout << "Main loop" << std::endl;
  
  // main loop
  return game.mainLoop();
}
