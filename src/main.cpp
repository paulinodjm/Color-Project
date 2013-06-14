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
    m_space = false;
    m_iTile = 0;
  }
  
  void setTileset(Tileset& tileset)
  {
    m_iTile = 0;
    m_tileset = &tileset;
    setSprite(m_tileset->getTileSprite(m_iTile));
  }
  
  void update(float deltaTime)
  {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) )
    {
      if (!m_space)
      {
        m_iTile++;
        if (m_iTile >= m_tileset->getTileCount())
        {
          m_iTile = 0;
        }
        setSprite(m_tileset->getTileSprite(m_iTile));
        m_space = true;
      }
    }
    else
    {
      m_space = false;
    }
  }
private:

  bool m_space;
  unsigned int m_iTile;
  Tileset* m_tileset;
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
  
  Tileset tileset;
  tileset.setTexture(*loader.get("data/tileset.png"), true);
  
  moFactory.getResources().addSprite("sprite", sprite);
  soFactory.getResources().addSprite("sprite", sprite);
  tFactory.getResources().addSprite("tileset", tileset.getTileSprite(0));
  
  // game initialisation
  Game game;
  game.addObjectFactory("myObject", moFactory);
  game.addObjectFactory("staticObject", soFactory);
  game.addObjectFactory("tilemap", tFactory);
  
  // object creation
  game.createObject("myObject");
  game.createObject("staticObject");
  Tilemap* tmap = (Tilemap*)game.createObject("tilemap");
  tmap->setPosition(200,10);
  tmap->setTileset(tileset);
  
  // main loop
  return game.mainLoop();
}
