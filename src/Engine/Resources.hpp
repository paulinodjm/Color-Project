//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////
#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include "BaseTypes.hpp"
#include "Tileset.hpp"
#include "Animation.hpp"

namespace e
{
  class Resources
  {
  public:

    sf::Texture* getTexture(const std::string& name);
    
    sf::Sprite* getSprite(const std::string& name);
    
    Tileset* getTileset(const std::string& name);
    
    Animation* getAnimation(const std::string& name);
    
    sf::SoundBuffer* getSoundBuffer(const std::string& name);
    
  //protected:
    
    bool addTexture(const std::string& name, sf::Texture* texture);
    
    bool addSprite(const std::string& name, const sf::Sprite& sprite);
    
    bool addTileset(const std::string& name, Tileset* tileset);
    
    bool addAnimation(const std::string& name, Animation* animation);
    
    bool addSoundBuffer(const std::string& name, sf::SoundBuffer* soundBuffer);
    
  private:

    std::map<std::string, sf::Texture*>     m_textures;
    
    std::map<std::string, sf::Sprite>       m_sprites;
    
    std::map<std::string, Tileset*>         m_tileset;
    
    std::map<std::string, Animation*>       m_animations;
    
    std::map<std::string, sf::SoundBuffer*> m_soundBuffers;
    
  friend class Game; /* Allows game to use addTexture and addSprite; */
  };
}

