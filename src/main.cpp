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
    std::cout << "dt : " << deltaTime << std::endl;
  
    bool up = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z);
    bool down = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S);
    bool left = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q);
    bool right = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D);
    
    sf::Vector2i position = getPosition();
    position.x += right - left;
    position.y += down - up;
    setPosition(position);
  }

private:

  sf::Texture m_texture;
  sf::Sprite m_sprite;
};

class MyObjectFactory : public ObjectFactory
{
public:

  Object* create()
  {
    return new MyObject();
  }
};

int main(int argc, char** argv)
{			
  MyObjectFactory factory;
  
  sf::Texture texture;
  texture.loadFromFile("data/tileset.png", sf::IntRect(0,0,32,32));
  sf::Sprite sprite(texture);

  Game game;
  game.addObjectFactory("myObject", factory);
  MyObject* mgo = (MyObject*)game.createObject("myObject");
  mgo->setSprite(sprite);
  return game.mainLoop();
}
