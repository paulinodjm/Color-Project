//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#include "animatedsprite.h"
#include <SFML/Graphics/RenderTarget.hpp>

ANIMATEDSPRITE::ANIMATEDSPRITE() : 
  DRAWABLE(),
  sf::Transformable(), 
  currentFrame(0), 
  playing(false), 
  looped(true),
  currentAnimation(nullptr)
{}

bool ANIMATEDSPRITE::Load(const std::string& name, CONTENTMANAGER& contentManager)
{
  if (contentManager.Load(animations, name))
  {
    SetAnimation(animations->begin()->first);
    if (!currentAnimation->Texture())
      std::cout << "problème" << std::endl;
    return true;
  }
  else
  {
    return false;
  }
}

bool ANIMATEDSPRITE::Save(const std::string& name)
{
  return false;
}


bool ANIMATEDSPRITE::SetAnimation(const std::string& name)
{
  auto it = animations->find(name);
  if (it == animations->end())
  {
    playing = false;
    return false;
  }
  
  currentAnimation = &(it->second);
  SetFrame(0);
}

bool ANIMATEDSPRITE::HasAnimation(const std::string& name) const
{
  return animations->find(name) != animations->end();
}

void ANIMATEDSPRITE::Play()
{
  playing = true;
}

void ANIMATEDSPRITE::Pause()
{
  playing = false;
}

void ANIMATEDSPRITE::Stop()
{
  playing = false;
  currentFrameTime = sf::Time::Zero;
}

void ANIMATEDSPRITE::SetLoop(bool enable)
{
  looped = enable;
}

bool ANIMATEDSPRITE::IsPlaying() const
{
  return playing;
}

bool ANIMATEDSPRITE::IsLooped()
{
  return looped;
}

void ANIMATEDSPRITE::SetFrame(int value)
{
  if (!currentAnimation) return;
  
  if (value < 0) 
  {
    value = 0;
  }
  else if (value > currentAnimation->FrameCount())
  {
    value = currentAnimation->FrameCount();
  }
  
  SetRect(currentAnimation->Frame(value));
  currentFrame = value;
}

int ANIMATEDSPRITE::CurrentFrame() const
{
  return currentFrame;
}

int ANIMATEDSPRITE::FrameCount() const
{
  if (currentAnimation)
  {
    return currentAnimation->FrameCount();
  }
  else
  {
    return 0;
  }
}

void ANIMATEDSPRITE::Update()
{
  if (playing && currentAnimation)
  {
    currentFrameTime += clock.restart();
    if (currentFrameTime >= currentAnimation->FrameTime())
    {
      if (currentFrame < currentAnimation->FrameCount()-1)
      {
        currentFrameTime -= currentAnimation->FrameTime();
        currentFrame++;
        SetRect(currentAnimation->Frame(currentFrame));
      }
      else
      {
        if (looped)
        {
          currentFrameTime -= currentAnimation->FrameTime();
          currentFrame = 0;
          SetRect(currentAnimation->Frame(currentFrame));
        }
        else
        {
          Stop();
        }
      }
    }
  }
}

void ANIMATEDSPRITE::SetRect(const sf::FloatRect rect)
{
  vertex[0].position = sf::Vector2f(0,0);
  vertex[1].position = sf::Vector2f(0, rect.height);
  vertex[2].position = sf::Vector2f(rect.width, rect.height);
  vertex[3].position = sf::Vector2f(rect.width, 0);

  vertex[0].texCoords = sf::Vector2f(rect.left, rect.top);
  vertex[1].texCoords = sf::Vector2f(rect.left, rect.top+rect.height);
  vertex[2].texCoords = sf::Vector2f(rect.left+rect.width, rect.top+rect.height);
  vertex[3].texCoords = sf::Vector2f(rect.left+rect.width, rect.top);
}

void ANIMATEDSPRITE::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  if (Visible() && currentAnimation)
  {
    states.transform *= getTransform();
    states.texture = &(*currentAnimation->Texture());
    target.draw(vertex, 4, sf::Quads, states);
  }
}

