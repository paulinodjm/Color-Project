//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#pragma once

#include "resources.h"
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>
#include <map>
#include <string>

class ANIMATION
{
public:

  ANIMATION();
  
  std::shared_ptr<TEXTURE>& Texture();
  void SetTexture(const std::shared_ptr<TEXTURE>& tex);
  
  void SetFirstFrame(const sf::FloatRect& frame);
  
  const sf::Time& FrameTime() const;
  void SetFrameTime(const sf::Time& time);
  
  int FrameCount() const;
  void SetFrameCount(int value);
  
  const sf::Vector2f& Origin() const;
  void SetOrigin(const sf::Vector2f& value);
  
  sf::FloatRect Frame(int i) const;

private:

  std::shared_ptr<TEXTURE> texture;
  sf::FloatRect firstFrame;
  sf::Time frameTime;
  int frameCount;
  sf::Vector2f origin;
};

typedef std::map<std::string, ANIMATION> ANIMATIONS;
