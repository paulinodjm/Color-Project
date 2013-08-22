//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#include "GameTypes.hpp"
#include "../Engine/Level.hpp"

/*

using namespace e;

///
/// MyObject
/// 
MyObject::MyObject(e::Resources& resources) : e::Object(resources), e::Solid(), e::Drawable(),
  m_tilemap(nullptr), m_move(false)
{
  m_sprite.setAnimation(*getResources()->getAnimation("idle"));
  m_sprite.setFrameTime(sf::seconds(0.15f));
  m_sprite.setOrigin(16,0);
  setBounds(sf::FloatRect(2,0,28,32));
}

void MyObject::calcView(sf::View& view) const
{
  view.setCenter(getPosition());
}

void MyObject::init(e::Level& level)
{
  m_tilemap = dynamic_cast<e::Tilemap*>( level.getObject("tilemap") );
  level.setCamera(this);
}

void MyObject::update(float deltaTime)
{
  bool up = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z);
  bool down = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S);
  bool left = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q);
  bool right = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D);
  
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::C))
  {
    setSolid(true);
    m_sprite.setColor(sf::Color::White);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::V))
  {
    setSolid(false);
    m_sprite.setColor(sf::Color(175,175,175,175));
  }
  
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

void MyObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(m_sprite);
}

void MyObject::moved()
{
  m_sprite.setPosition(getPosition().x + 16, getPosition().y);
}

///
/// StaticObject
///
StaticObject::StaticObject(e::Resources& resources) : e::GameObject(resources),
  m_soundBuffer("data/sound.wav")
{
  setSprite(*resources.getSprite("white"));
  setBounds(sf::FloatRect(0,0,32,32));
  m_sound.setBuffer(e::SoundBuffer("data/sound.wav"));
}

void StaticObject::update(float deltaTime)
{
}

void StaticObject::touch(const Solid& solid)
{
  setSprite(*(getResources()->getSprite("red")));
  m_sound.play();
}

void StaticObject::untouch(const Solid& solid)
{
  setSprite(*(getResources()->getSprite("white")));
}

e::SoundPlayer StaticObject::m_sound;

///
/// object factories declaration
///
AutoFactory<MyObject>     moFactory;
AutoFactory<StaticObject> soFactory;
AutoFactory<e::Tilemap>   tmFactory;
//*/

