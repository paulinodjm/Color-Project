//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#pragma once

#include "resources.h"
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <memory>
#include <map>
#include <string>

class ANIMATION
{
public:

  ANIMATION();
  
  std::shared_ptr<TEXTURE> Texture() const;
  void SetTexture(const std::shared_ptr<TEXTURE>& tex);
  
  void SetFirstFrame(const sf::FloatRect& frame);
  
  const sf::Time& FrameTime() const;
  void SetFrameTime(const sf::Time& time);
  
  int FrameCount() const;
  void SetFrameCount(int value);
  
  sf::FloatRect Frame(int i) const;

private:

  std::shared_ptr<TEXTURE> texture;
  sf::FloatRect firstFrame;
  sf::Time frameTime;
  int frameCount;
};

typedef std::map<std::string, ANIMATION> ANIMATIONS;
