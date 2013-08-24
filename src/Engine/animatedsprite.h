//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#pragma once

#include "drawable.h"
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Clock.hpp>
#include "animation.h"
#include "contentmanager.h"
#include <memory>

class ANIMATEDSPRITE : public DRAWABLE, public sf::Transformable
{
public:

  ANIMATEDSPRITE();
  
  bool Load(const std::string& name, CONTENTMANAGER& contentManager);
  bool Save(const std::string& name);
  
  
  bool SetAnimation(const std::string& name);
  bool HasAnimation(const std::string& name) const;
  
  void Play();
  void Pause();
  void Stop();
  void SetLoop(bool enable);
  
  bool IsPlaying() const;
  bool IsLooped();
  
  void SetFrame(int value);
  int CurrentFrame() const;
  int FrameCount() const;
  
  void Update();    

protected:

  void SetRect(const sf::FloatRect rect);
  void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:

  std::shared_ptr<ANIMATIONS>   animations;
  ANIMATION*                    currentAnimation;
  sf::Vertex                    vertex[4];
  int                           currentFrame;
  sf::Time                      currentFrameTime;
  sf::Clock                     clock;
  bool                          playing;
  bool                          looped;
};
