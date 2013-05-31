//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////

#include <iostream>
#include "Game.hpp"
#include "Object.hpp"
#include <string>
#include <SFML/Graphics.hpp>

class MyObject : public Object, public Drawable
{
public:

  MyObject() : Object()
  {
    m_texture.loadFromFile("data/tileset.png", sf::IntRect(0,0,32,32));
    m_sprite.setTexture(m_texture);
  }

protected:

  void update(float deltaTime)
  {
    bool up = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z);
    bool down = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S);
    bool left = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q);
    bool right = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D);

    m_sprite.move(right-left, down-up);
  }

  void draw(sf::RenderTarget& target, sf::RenderStates states) const
  {
    target.draw(m_sprite);
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
  Object *obj = factory.create();

  Game game;
  game.addObjectFactory("myObject", factory);
  std::cout << game.createObject("obj") << std::endl;
  std::cout << game.createObject("myObject") << std::endl;
  return game.mainLoop();
}
