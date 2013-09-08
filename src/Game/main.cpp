//////////////////////////////////////////////////////////
/// Copyright 2013 Marié Paulino (paulinodjm@hotmail.com)
/// Licence : Simplified BSD Licence (see inclued LICENCE)
//////////////////////////////////////////////////////////

#include <cstdlib>
#include <string>
#include <map>
#include "../Engine/level.h"
#include "../Engine/contentmanager.h"
#include "../Engine/objectfactory.h"
#include "gametypes.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>

using namespace std;

void InitGameTypes(map<string, OBJECTFACTORY*>& gameTypes)
{
  #define GAMETYPE(type) gameTypes.insert( pair<string, OBJECTFACTORY*>( #type, new TOBJECTFACTORY<type> ) )
  GAMETYPE(PLAYER);
  GAMETYPE(STATICOBJECT);
  #undef GAMETYPE
}

/************************************
* main                              *
************************************/
int main(int argc, char** argv)
{	
  CONTENTMANAGER  contentManager;
  LEVEL           level;
  map<string, OBJECTFACTORY*> gameTypes;
  
  InitGameTypes(gameTypes);
  std::cout << "==== GameTypes ====" << std::endl;
  for (auto it : gameTypes)
  {
    std::cout << it.first << std::endl;
  }
		
  sf::RenderWindow rendow(sf::VideoMode(800,600), L"Color-Project", sf::Style::Titlebar);
  rendow.setFramerateLimit(60);
  sf::Event event;
  
  if (!level.Load("data/levels/objects.json", contentManager, gameTypes))
    return EXIT_FAILURE;
    
  PLAYER *player = new PLAYER;
  STATICOBJECT *staticobj = new STATICOBJECT;
  if (!player->Load(contentManager) || !staticobj->Load(contentManager))
    return EXIT_FAILURE;
  level.AddObject(player, "player");
  level.AddObject(staticobj, "static");
    
  level.Init();
  while (rendow.isOpen())
  {
    while (rendow.pollEvent(event))
    {
      if (event.type == sf::Event::Closed
        || (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)
      ){
        rendow.close();
      }
    }
    
    level.Update();
    level.PerformMove();
    level.PerformCollisions();
    
    rendow.draw(level);
    rendow.display();
  }

  return EXIT_SUCCESS;
}//*/

