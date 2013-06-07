//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////

#include <iostream>
#include "Game.hpp"
#include "GameObject.hpp"
#include <string>
#include <SFML/Graphics.hpp>

class MyObject : public GameObject
{
public:

  MyObject() : GameObject()
  {
    setPosition(50, 50);
  }

protected:

  void update(float deltaTime)
  {
    bool up = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z);
    bool down = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S);
    bool left = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q);
    bool right = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D);
    
    sf::Vector2i position = getPosition();
    position.x += (right - left);
    position.y += (down - up);
    setPosition(position);
  }

  void touch(const Solid& solid)
  {
    std::cout << "touche " << (&solid) << std::endl;
  }
  
  void untouch(const Solid& solid)
  {
    std::cout << "quitte " << (&solid) << std::endl;
  }
};

class MyObjectFactory : public ObjectFactory
{
public:

  Object* create()
  {
    return new MyObject();
  }
};

class StaticObject : public GameObject
{
public:

  StaticObject() : GameObject()
  {
    setBounds(sf::IntRect(0,0,32,32));
  }
};

class StaticObjectFactory : public ObjectFactory
{
public:

  Object* create()
  {
    return new StaticObject();
  }
};

/************************************
* main                              *
************************************/
int main(int argc, char** argv)
{			
  MyObjectFactory moFactory;
  StaticObjectFactory soFactory;
  
  sf::Texture texture;
  texture.loadFromFile("data/tileset.png", sf::IntRect(0,0,32,32));
  sf::Sprite sprite(texture);

  Game game;
  game.addObjectFactory("myObject", moFactory);
  game.addObjectFactory("staticObject", soFactory);
  
  MyObject* mgo = (MyObject*)game.createObject("myObject");
  mgo->setSprite(sprite);
  mgo->setBounds(sf::IntRect(0,0,32,32));
  
  ((GameObject*)game.createObject("staticObject"))->setSprite(sprite);
  GameObject* go = (GameObject*)game.createObject("staticObject");
  go->setSprite(sprite);
  go->setPosition(100,100);
  
  go = (GameObject*)game.createObject("staticObject");
  go->setSprite(sprite);
  go->setPosition(32,0);
  //*/
  
  return game.mainLoop();
}
