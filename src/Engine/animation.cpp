//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#include "animation.h"

ANIMATION::ANIMATION() : frameCount(0) {}

std::shared_ptr<TEXTURE>& ANIMATION::Texture()
{
  return texture;
}

void ANIMATION::SetTexture(const std::shared_ptr<TEXTURE>& tex)
{
  texture = tex;
}

void ANIMATION::SetFirstFrame(const sf::FloatRect& frame)
{
  firstFrame = frame;
}

const sf::Time& ANIMATION::FrameTime() const
{
  return frameTime;
}

void ANIMATION::SetFrameTime(const sf::Time& time)
{
  frameTime = time;
}

int ANIMATION::FrameCount() const
{
  return frameCount;
}

void ANIMATION::SetFrameCount(int value)
{
  if (value > 0)
  {
    frameCount = value;
  }
  else
  {
    frameCount = 0;
  }
}

const sf::Vector2f& ANIMATION::Origin() const
{
  return origin;
}

void ANIMATION::SetOrigin(const sf::Vector2f& value)
{
  origin = value;
}

sf::FloatRect ANIMATION::Frame(int i) const
{
  sf::FloatRect frame = firstFrame;
  if (i > 0 && i < frameCount)
  {
    frame.left += frame.width * i;
  }
  return frame;
}
